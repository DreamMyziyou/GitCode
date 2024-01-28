//
// Created by WeslyChen on 2024/1/24.
//

#include "VulkanResource.h"

#include "VulkanManager.h"

using namespace std;

QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int32 i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (indices.IsComplete())
            break;

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, VulkanManager::instance()->GetSurface(), &presentSupport);
        if (presentSupport)
            indices.presentFamily = i;

        i++;
    }

    return indices;
}
