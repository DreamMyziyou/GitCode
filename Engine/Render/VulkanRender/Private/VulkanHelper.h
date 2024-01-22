//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANHELPER_H
#define WORKENGINE_VULKANHELPER_H

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <optional>
#include <vector>

#include "Engine/EngineCore.h"

struct QueueFamilyIndices
{
    std::optional<uint32> graphicsFamily{};
    std::optional<uint32> presentFamily{};

    bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

#endif  // WORKENGINE_VULKANHELPER_H
