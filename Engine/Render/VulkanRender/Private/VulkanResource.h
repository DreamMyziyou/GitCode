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

#include "Core/World/World.h"
#include "Engine.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

struct IVulkanSubSystem
{
    virtual ~IVulkanSubSystem() = default;

    virtual void OnInit() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnUpdate() = 0;
};

class VkRCenter final
{
    SINGLETON_CLASS(VkRCenter)

    entt::registry world;

    entt::entity windowEntity = entt::null;

    template <typename T>
    T* GetComponentFromWindow()
    {
        if (windowEntity == entt::null)
            return nullptr;

        return world.try_get<T>(windowEntity);
    }
};

#endif  // WORKENGINE_VULKANRESOURCE_H
