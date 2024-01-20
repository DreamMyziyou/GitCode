//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Common/DeleteMacro.h"
#include "Logger/Logger.h"

GlfwWindow::GlfwWindow()
{
    Logger::Log(Logger::Level::Info, "Window", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
}

GlfwWindow::~GlfwWindow()
{
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    Logger::Log(Logger::Level::Info, "Window", "Destroy GlfwWindow.");
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
