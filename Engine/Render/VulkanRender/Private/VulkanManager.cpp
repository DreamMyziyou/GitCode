//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindow.h"
#include "VulkanManagerImpl.h"

using namespace std;

void VulkanManager::StartupModule()
{
    IModule::StartupModule();

    mImpl = new VulkanManagerImpl();

    mImpl->InitGlfw();
    mImpl->InitVulkan();
}

void VulkanManager::ShutdownModule()
{
    mImpl->UninitVulkan();
    mImpl->UninitGlfw();

    SAFE_DELETE(mImpl);

    IModule::ShutdownModule();
}

std::shared_ptr<Render::IWindow> VulkanManager::CreateGlfwWindow()
{
    auto glfwWindow = make_shared<GlfwWindow>();
    glfwWindow->Create();
    return glfwWindow;
}
