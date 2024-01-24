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

void GlfwWindow::Run()
{
    if (!mWindow)
        return;

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
    }
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
    if (mWindow != nullptr)
        return;

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);
}

void GlfwWindow::Destroy()
{
    if (nullptr == mWindow)
        return;

    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    Logger::Log(Logger::Level::Info, "VulkanRender", "Destroy GlfwWindow.");
}
