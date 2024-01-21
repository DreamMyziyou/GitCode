//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindow.h"

using namespace std;

void VulkanManager::StartupModule()
{
    IModule::StartupModule();

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void VulkanManager::ShutdownModule()
{
    glfwTerminate();

    IModule::ShutdownModule();
}

std::shared_ptr<Render::IWindow> VulkanManager::CreateGlfwWindow()
{
    auto glfwWindow = make_shared<GlfwWindow>();
    glfwWindow->Create();
    return glfwWindow;
}
