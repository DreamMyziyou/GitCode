//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanDeviceWrapper.h"

#include <map>
#include <set>
#include <vector>

#include "Core/Engine/Engine.h"
#include "VulkanManager.h"

using namespace std;

static const vector<const char*> gDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

void VulkanDeviceWrapper::CreateResource()
{
    CreatePhysicalDevice();
    CreateLogicDevice();
    CreateCommand();

    mSyncObject = make_shared<VulkanSyncWrapper>();
    mSyncObject->CreateResource();
}

void VulkanDeviceWrapper::DestroyResource()
{
    if (nullptr == mSyncObject)
        return;

    mSyncObject->DestroyResource();
    mSyncObject = nullptr;

    vkDestroyCommandPool(mLogicDevice, mCommandPool, nullptr);
    mCommandPool = nullptr;

    vkDestroyDevice(mLogicDevice, nullptr);
    mLogicDevice = nullptr;
}

uint32 VulkanDeviceWrapper::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
    }

    return 0;
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

    auto surfaceWrapper = VulkanManager::instance()->GetSurfaceWrapper();

    auto indices = surfaceWrapper->FindQueueFamilies(device);
    if (!indices.IsComplete())
        return false;

    bool extensionsSupported = CheckDeviceExtensionSupport(device);
    if (!extensionsSupported)
        return false;

    auto swapChainSupport = surfaceWrapper->QuerySwapChainSupport(device);
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

    VulkanManager::instance()->GetSurfaceWrapper()->OnUpdate(mPhysicalDevice);
}

void VulkanDeviceWrapper::CreateLogicDevice()
{
    if (!mPhysicalDevice)
        return;

    auto surfaceWrapper = VulkanManager::instance()->GetSurfaceWrapper();
    auto indices = surfaceWrapper->FindQueueFamilies(mPhysicalDevice);

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
    auto surfaceWrapper = VulkanManager::instance()->GetSurfaceWrapper();
    auto indices = surfaceWrapper->FindQueueFamilies(mPhysicalDevice);
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = indices.graphicsFamily.value();
    VkCommandPool commandPool;
    auto vkResult = vkCreateCommandPool(mLogicDevice, &poolInfo, nullptr, &commandPool);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    mCommandPool = commandPool;

    mCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)mCommandBuffers.size();
    vkAllocateCommandBuffers(mLogicDevice, &allocInfo, mCommandBuffers.data());
}
