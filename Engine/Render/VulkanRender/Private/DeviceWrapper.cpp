//
// Created by WeslyChen on 2024/1/21.
//

#include "DeviceWrapper.h"

#include <map>
#include <set>
#include <vector>

#include "Engine/EngineCore.h"

using namespace std;

void DeviceWrapper::InitDevice(VkInstance instance, VkSurfaceKHR surface)
{
    if (!instance || !surface)
        return;
    mInstance = instance;
    mSurface = surface;

    CreatePhysicalDevice();
    CreateLogicDevice();
}

void DeviceWrapper::UninitDevice()
{
    if (mLogicDevice)
    {
        vkDestroyDevice(mLogicDevice, nullptr);
        mLogicDevice = nullptr;
    }
}

bool DeviceWrapper::IsDeviceSuitable(VkPhysicalDevice device) const
{
    if (!device)
        return false;

    QueueFamilyIndices indices = FindQueueFamilies(device);
    if (!indices.IsComplete())
        return false;

    return true;
}

int32 DeviceWrapper::ScoreDeviceSuitability(VkPhysicalDevice device) const
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

QueueFamilyIndices DeviceWrapper::FindQueueFamilies(VkPhysicalDevice device) const
{
    QueueFamilyIndices indices;

    uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int32 i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (indices.IsComplete())
            break;

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, mSurface, &presentSupport);
        if (presentSupport)
            indices.presentFamily = i;

        i++;
    }

    return indices;
}

void DeviceWrapper::CreatePhysicalDevice()
{
    // Get device
    uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(mInstance, &deviceCount, nullptr);
    if (deviceCount == 0)
        return Logger::LogFatal("VulkanRender", "Failed to find GPUs with Vulkan support!");
    vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(mInstance, &deviceCount, devices.data());

    // Use an ordered map to automatically sort candidates by increasing score
    std::multimap<int32, VkPhysicalDevice> candidates;
    for (const auto& device : devices)
    {
        int32 score = ScoreDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0)
        mPhysicalDevice = candidates.rbegin()->second;
    else
        return Logger::LogFatal("VulkanRender", "Failed to find a suitable GPU!");
}

void DeviceWrapper::CreateLogicDevice()
{
    if (!mPhysicalDevice)
        return;

    QueueFamilyIndices indices = FindQueueFamilies(mPhysicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

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

    if (vkCreateDevice(mPhysicalDevice, &createInfo, nullptr, &mLogicDevice) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create logical device!");

    vkGetDeviceQueue(mLogicDevice, indices.presentFamily.value(), 0, &mGraphicsQueue);
}