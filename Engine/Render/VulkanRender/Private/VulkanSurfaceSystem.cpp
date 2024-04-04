//
// Created by WeslyChen on 2024/1/28.
//
#include <algorithm>
#include <limits>

#include "GlfwWindowComponent.h"
#include "VulkanComponent.h"
#include "VulkanSurfaceSystem.h"

using namespace std;

void VulkanSurfaceSystem::OnInit()
{
    auto windowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (!windowComponent || !windowComponent->window)
        return;
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (!vulkanComponent)
        return;
    if (VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>())
        return;

    auto& surfaceComponent = VkRCenter::instance()->world.emplace<VulkanSurfaceComponent>(VkRCenter::instance()->vulkanEntity);

    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(windowComponent->window);
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = nullptr;
    if (vkCreateWin32SurfaceKHR(vulkanComponent->instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create window surface!");
    else
        surfaceComponent.surface = surface;
}

void VulkanSurfaceSystem::OnDestroy()
{
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (!vulkanComponent)
        return;
    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent || !surfaceComponent->surface)
        return;

    vkDestroySurfaceKHR(vulkanComponent->instance, surfaceComponent->surface, nullptr);
    VkRCenter::instance()->world.remove<VulkanSurfaceComponent>(VkRCenter::instance()->vulkanEntity);
}

void VulkanSurfaceSystem::OnUpdate() {}
