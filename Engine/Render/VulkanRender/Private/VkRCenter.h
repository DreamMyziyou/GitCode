//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANRESOURCE_H
#define WORLDENGINE_VULKANRESOURCE_H

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <memory>
#include <optional>
#include <vector>

#include "Core/World/World.h"
#include "Engine.h"

class VkRCenter final
{
    SINGLETON_CLASS(VkRCenter)

    entt::registry world;

    entt::entity windowEntity = entt::null;
    entt::entity vulkanEntity = entt::null;

    template <typename T>
    T* GetComponentFromWindow()
    {
        if (windowEntity == entt::null)
            return nullptr;

        return world.try_get<T>(windowEntity);
    }

    template <typename T>
    T* GetComponentFromVulkan()
    {
        if (vulkanEntity == entt::null)
            return nullptr;

        return world.try_get<T>(vulkanEntity);
    }
};

#endif  // WORLDENGINE_VULKANRESOURCE_H
