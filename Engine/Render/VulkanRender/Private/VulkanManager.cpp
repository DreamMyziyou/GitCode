//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

using namespace std;

void VulkanManager::StartupModule() {}

void VulkanManager::ShutdownModule()
{
    mDevice.Destroy();

    DestroySurface();

    mMainWindow.Destroy();

    mInstance.UninitVulkanInstance();

    TerminalGlfw();
}

Render::IMainWindow* VulkanManager::CreateMainWindow(int width, int height, String title)
{
    if (mMainWindow.GetWindow() != nullptr)
        return &mMainWindow;

    InitGlfw();

    mMainWindow.SetWH(width, height);
    mMainWindow.SetWindowName(title);
    mMainWindow.Create();

    mInstance.InitVulkanInstance();

    CreateSurface();

    mDevice.Create();

    return &mMainWindow;
}

void VulkanManager::InitGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void VulkanManager::TerminalGlfw()
{
    glfwTerminate();
}

void VulkanManager::CreateSurface()
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(mMainWindow.GetWindow());
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = nullptr;
    if (vkCreateWin32SurfaceKHR(mInstance.GetVulkanInstance(), &createInfo, nullptr, &surface) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create window surface!");
    else
        mSurface = surface;
}

void VulkanManager::DestroySurface()
{
    if (nullptr == mSurface)
        return;

    vkDestroySurfaceKHR(mInstance.GetVulkanInstance(), mSurface, nullptr);
    mSurface = nullptr;
}
