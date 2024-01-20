//
// Created by WeslyChen on 2024/1/20.
//

#include "WindowManager.h"

#include "GlfwWindow.h"

using namespace std;

void WindowManager::StartupModule()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void WindowManager::ShutdownModule()
{
    glfwTerminate();
}

std::shared_ptr<WindowInterface::IWindow> WindowManager::CreateWindow()
{
    return make_shared<GlfwWindow>();
}
