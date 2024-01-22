//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Module/Logger/Logger.h"

GlfwWindow::GlfwWindow() {}

GlfwWindow::~GlfwWindow()
{
    Destroy();
}

void GlfwWindow::SetWH(int32 width, int32 height)
{
    mWidth = width;
    mHeight = height;
}

void GlfwWindow::SetWindowName(const String& name)
{
    mWindowName = name;
}

void GlfwWindow::Create()
{
    if (mWindow)
        return;

    mInstance.InitVulkanInstance();

    InitWindow();

    InitSurface();

    mDevice.InitDevice(mInstance.GetVulkanInstance(), mSurface);
}

void GlfwWindow::Run()
{
    if (!mWindow)
        return;

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
    }
}

void GlfwWindow::InitWindow()
{
    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);
}

void GlfwWindow::InitSurface()
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(mWindow);
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = nullptr;
    if (vkCreateWin32SurfaceKHR(mInstance.GetVulkanInstance(), &createInfo, nullptr, &surface) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create window surface!");
    else
        mSurface = surface;
}

void GlfwWindow::Destroy()
{
    if (!mInstance.GetVulkanInstance())
        return;

    if (mSurface)
    {
        vkDestroySurfaceKHR(mInstance.GetVulkanInstance(), mSurface, nullptr);
        mSurface = nullptr;
    }

    if (mWindow)
    {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
        Logger::Log(Logger::Level::Info, "VulkanRender", "Destroy GlfwWindow.");
    }

    mDevice.UninitDevice();
    mInstance.UninitVulkanInstance();
}
