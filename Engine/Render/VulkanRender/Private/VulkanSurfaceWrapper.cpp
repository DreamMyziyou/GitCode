//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanSurfaceWrapper.h"

#include "VulkanManager.h"

void VulkanSurfaceWrapper::CreateResource()
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(VulkanManager::instance()->GetWindowHandle());
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = nullptr;
    if (vkCreateWin32SurfaceKHR(VulkanManager::instance()->GetVulkanInstance(), &createInfo, nullptr, &surface) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create window surface!");
    else
        mSurface = surface;
}

void VulkanSurfaceWrapper::DestroyResource()
{
    if (nullptr == mSurface)
        return;

    vkDestroySurfaceKHR(VulkanManager::instance()->GetVulkanInstance(), mSurface, nullptr);
    mSurface = nullptr;
}
