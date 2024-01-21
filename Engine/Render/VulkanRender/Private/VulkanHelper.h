//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANHELPER_H
#define WORKENGINE_VULKANHELPER_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

#include "Engine/EngineCore.h"

struct QueueFamilyIndices
{
    std::optional<uint32> graphicsFamily{};

    bool IsComplete() const { return graphicsFamily.has_value(); }
};

inline QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
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
        i++;
    }

    return indices;
}

#endif  // WORKENGINE_VULKANHELPER_H
