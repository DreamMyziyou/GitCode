//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanDeviceSystem.h"

#include <map>
#include <set>
#include <vector>

#include "Engine.h"
#include "VulkanComponent.h"

using namespace std;

static const vector<const char*> gDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

void VulkanDeviceSystem::OnInit()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (deviceComponent)
        return;

    VkRCenter::instance()->world.emplace<VulkanDeviceComponent>(VkRCenter::instance()->vulkanEntity);

    CreatePhysicalDevice();
    CreateLogicDevice();
    CreateCommand();
    CreateSync();
}

void VulkanDeviceSystem::OnDestroy()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    for (auto& item : deviceComponent->imageAvailableSemaphores)
        vkDestroySemaphore(deviceComponent->logicDevice, item, nullptr);
    deviceComponent->imageAvailableSemaphores.clear();
    for (auto& item : deviceComponent->renderFinishedSemaphores)
        vkDestroySemaphore(deviceComponent->logicDevice, item, nullptr);
    deviceComponent->renderFinishedSemaphores.clear();
    for (auto& item : deviceComponent->inFlightFences)
        vkDestroyFence(deviceComponent->logicDevice, item, nullptr);
    deviceComponent->inFlightFences.clear();

    vkDestroyCommandPool(deviceComponent->logicDevice, deviceComponent->commandPool, nullptr);
    vkDestroyDevice(deviceComponent->logicDevice, nullptr);
    VkRCenter::instance()->world.remove<VulkanDeviceComponent>(VkRCenter::instance()->vulkanEntity);
}

void VulkanDeviceSystem::OnUpdate() {}

bool VulkanDeviceSystem::CheckDeviceExtensionSupport(VkPhysicalDevice device) const
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

bool VulkanDeviceSystem::IsDeviceSuitable(VkPhysicalDevice device) const
{
    if (!device)
        return false;

    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent)
        return false;

    auto indices = surfaceComponent->FindQueueFamilies(device);
    if (!indices.IsComplete())
        return false;

    bool extensionsSupported = CheckDeviceExtensionSupport(device);
    if (!extensionsSupported)
        return false;

    auto swapChainSupport = surfaceComponent->QuerySwapChainSupport(device);
    bool swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

    if (!swapChainAdequate)
        return false;

    return true;
}

int32 VulkanDeviceSystem::ScoreDeviceSuitability(VkPhysicalDevice device) const
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

void VulkanDeviceSystem::CreatePhysicalDevice()
{
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();

    // Get device
    uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanComponent->instance, &deviceCount, nullptr);
    if (deviceCount == 0)
        return Logger::LogFatal("VulkanRender", "Failed to find GPUs with Vulkan support!");
    vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanComponent->instance, &deviceCount, devices.data());

    // Use an ordered map to automatically sort candidates by increasing score
    multimap<int32, VkPhysicalDevice> candidates;
    for (const auto& device : devices)
    {
        int32 score = ScoreDeviceSuitability(device);
        candidates.insert(make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0)
        deviceComponent->physicalDevice = candidates.rbegin()->second;
    else
        return Logger::LogFatal("VulkanRender", "Failed to find a suitable GPU!");

    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent)
        return;
    surfaceComponent->update(deviceComponent->physicalDevice);
}

void VulkanDeviceSystem::CreateLogicDevice()
{
    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice)
        return;

    auto indices = surfaceComponent->FindQueueFamilies(deviceComponent->physicalDevice);
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

    if (vkCreateDevice(deviceComponent->physicalDevice, &createInfo, nullptr, &deviceComponent->logicDevice) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create logical device!");

    vkGetDeviceQueue(deviceComponent->logicDevice, indices.graphicsFamily.value(), 0, &deviceComponent->graphicsQueue);
    vkGetDeviceQueue(deviceComponent->logicDevice, indices.presentFamily.value(), 0, &deviceComponent->presentQueue);
}

void VulkanDeviceSystem::CreateCommand()
{
    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice)
        return;

    auto indices = surfaceComponent->FindQueueFamilies(deviceComponent->physicalDevice);
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = indices.graphicsFamily.value();
    VkCommandPool commandPool;
    auto vkResult = vkCreateCommandPool(deviceComponent->logicDevice, &poolInfo, nullptr, &commandPool);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    deviceComponent->commandPool = commandPool;

    deviceComponent->commandBuffers.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)deviceComponent->commandBuffers.size();
    vkAllocateCommandBuffers(deviceComponent->logicDevice, &allocInfo, deviceComponent->commandBuffers.data());
}

void VulkanDeviceSystem::CreateSync()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    deviceComponent->imageAvailableSemaphores.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    deviceComponent->renderFinishedSemaphores.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    deviceComponent->inFlightFences.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; ++i)
    {
        auto vkResult = vkCreateSemaphore(deviceComponent->logicDevice, &semaphoreInfo, nullptr, &deviceComponent->imageAvailableSemaphores[i]);
        if (vkResult != VK_SUCCESS)
            return;

        vkResult = vkCreateSemaphore(deviceComponent->logicDevice, &semaphoreInfo, nullptr, &deviceComponent->renderFinishedSemaphores[i]);
        if (vkResult != VK_SUCCESS)
            return;

        vkResult = vkCreateFence(deviceComponent->logicDevice, &fenceInfo, nullptr, &deviceComponent->inFlightFences[i]);
        if (vkResult != VK_SUCCESS)
            return;
    }
}
