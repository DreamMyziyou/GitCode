//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANHELPER_H
#define WORKENGINE_VULKANHELPER_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>

#include "Engine/EngineCore.h"

struct QueueFamilyIndices
{
    std::optional<uint32> graphicsFamily{};

    bool IsComplete() const { return graphicsFamily.has_value(); }
};

#endif  // WORKENGINE_VULKANHELPER_H
