//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANRESOURCE_H
#define WORKENGINE_VULKANRESOURCE_H

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <memory>
#include <optional>
#include <vector>

#include "Core/Engine/EngineCore.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

struct IVulkanResource
{
    virtual ~IVulkanResource() = default;

    virtual void CreateResource() = 0;
    virtual void DestroyResource() = 0;
};

#endif  // WORKENGINE_VULKANRESOURCE_H
