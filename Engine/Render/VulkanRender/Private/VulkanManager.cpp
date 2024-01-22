//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "VulkanManagerImpl.h"

using namespace std;

void VulkanManager::StartupModule()
{
    mImpl = new VulkanManagerImpl();
    mImpl->InitGlfwVulkan();
}

void VulkanManager::ShutdownModule()
{
    mImpl->UninitGlfwVulkan();
    SAFE_DELETE(mImpl);
}

Render::IMainWindow* VulkanManager::GetMainWindow() const
{
    if (!mImpl)
        return nullptr;

    return &mImpl->mMainWindow;
}
