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

#include <optional>
#include <vector>

#include "Engine/EngineCore.h"

struct QueueFamilyIndices
{
    std::optional<uint32> graphicsFamily{};
    std::optional<uint32> presentFamily{};

    bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
};
extern QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};
extern SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

struct IVulkanResource
{
    virtual ~IVulkanResource() = default;

    virtual VkInstance GetVulkanInstance() const = 0;
    virtual GLFWwindow* GetWindowHandle() const = 0;
    virtual VkSurfaceKHR GetSurface() const = 0;
    virtual VkPhysicalDevice GetPhysicalDevice() const = 0;
    virtual VkDevice GetVulkanDevice() const = 0;
    virtual VkQueue GetGraphicsQueue() const = 0;
    virtual VkSwapchainKHR GetSwapChain() const = 0;
};
extern IVulkanResource* GetVulkanResource();

#endif  // WORKENGINE_VULKANRESOURCE_H
