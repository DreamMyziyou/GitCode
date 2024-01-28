//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanDeviceWrapper.h"

#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <vector>

#include "Engine/EngineCore.h"
#include "VulkanManager.h"

using namespace std;

static const vector<const char*> gDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

void VulkanDeviceWrapper::CreateResource()
{
    auto vulkanInstance = VulkanManager::instance()->GetVulkanInstance();
    auto surface = VulkanManager::instance()->GetSurface();
    if (!vulkanInstance || !surface)
        return;

    CreatePhysicalDevice();
    CreateLogicDevice();
    CreateCommand();
}

void VulkanDeviceWrapper::DestroyResource()
{
    if (!mCommandPool)
        return;

    vkDestroyCommandPool(mLogicDevice, mCommandPool, nullptr);
    mCommandPool = nullptr;

    vkDestroyDevice(mLogicDevice, nullptr);
    mLogicDevice = nullptr;
}

bool VulkanDeviceWrapper::CheckDeviceExtensionSupport(VkPhysicalDevice device) const
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    set<String> requiredExtensions(gDeviceExtensions.begin(), gDeviceExtensions.end());

    for (const auto& extension : availableExtensions)
        requiredExtensions.erase(extension.extensionName);

    return requiredExtensions.empty();
}

bool VulkanDeviceWrapper::IsDeviceSuitable(VkPhysicalDevice device) const
{
    if (!device)
        return false;

    QueueFamilyIndices indices = FindQueueFamilies(device);
    if (!indices.IsComplete())
        return false;

    bool extensionsSupported = CheckDeviceExtensionSupport(device);
    if (!extensionsSupported)
        return false;

    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
    bool swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

    if (!swapChainAdequate)
        return false;

    return true;
}

int32 VulkanDeviceWrapper::ScoreDeviceSuitability(VkPhysicalDevice device) const
{
    if (!IsDeviceSuitable(device))
        return 0;

    int32 score = 0;

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
        return 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    return score;
}

VulkanDeviceWrapper::SwapChainSupportDetails VulkanDeviceWrapper::QuerySwapChainSupport(VkPhysicalDevice device) const
{
    SwapChainSupportDetails details;

    auto surface = VulkanManager::instance()->GetSurface();
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

VkSurfaceFormatKHR VulkanDeviceWrapper::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const
{
    for (const auto& availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return availableFormat;
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanDeviceWrapper::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const
{
    for (const auto& availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanDeviceWrapper::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        return capabilities.currentExtent;

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice, VulkanManager::instance()->GetSurface(), &surfaceCapabilities);

    VkExtent2D actualExtent = surfaceCapabilities.currentExtent;

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

void VulkanDeviceWrapper::CreatePhysicalDevice()
{
    // Get device
    uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(VulkanManager::instance()->GetVulkanInstance(), &deviceCount, nullptr);
    if (deviceCount == 0)
        return Logger::LogFatal("VulkanRender", "Failed to find GPUs with Vulkan support!");
    vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(VulkanManager::instance()->GetVulkanInstance(), &deviceCount, devices.data());

    // Use an ordered map to automatically sort candidates by increasing score
    multimap<int32, VkPhysicalDevice> candidates;
    for (const auto& device : devices)
    {
        int32 score = ScoreDeviceSuitability(device);
        candidates.insert(make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0)
        mPhysicalDevice = candidates.rbegin()->second;
    else
        return Logger::LogFatal("VulkanRender", "Failed to find a suitable GPU!");
}

void VulkanDeviceWrapper::CreateLogicDevice()
{
    if (!mPhysicalDevice)
        return;

    QueueFamilyIndices indices = FindQueueFamilies(mPhysicalDevice);

    vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(gDeviceExtensions.size());
    createInfo.ppEnabledExtensionNames = gDeviceExtensions.data();

    if (vkCreateDevice(mPhysicalDevice, &createInfo, nullptr, &mLogicDevice) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create logical device!");

    vkGetDeviceQueue(mLogicDevice, indices.graphicsFamily.value(), 0, &mGraphicsQueue);
    vkGetDeviceQueue(mLogicDevice, indices.presentFamily.value(), 0, &mPresentQueue);
}

void VulkanDeviceWrapper::CreateCommand()
{
    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(mPhysicalDevice);
    mSurfaceCapabilities = swapChainSupport.capabilities;
    mExpectSurfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    mExpectPresentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    mExpectSwapChainExtent = ChooseSwapExtent(swapChainSupport.capabilities);
    uint32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        imageCount = swapChainSupport.capabilities.maxImageCount;
    mExpectSwapChainBufferCount = imageCount;

    QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(mPhysicalDevice);
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    VkCommandPool commandPool;
    auto vkResult = vkCreateCommandPool(mLogicDevice, &poolInfo, nullptr, &commandPool);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    mCommandPool = commandPool;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;
    VkCommandBuffer commandBuffer;
    vkResult = vkAllocateCommandBuffers(mLogicDevice, &allocInfo, &commandBuffer);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    mCommandBuffer = commandBuffer;
}
