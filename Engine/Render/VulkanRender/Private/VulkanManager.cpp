//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

using namespace std;

void VulkanManager::StartupModule() {}

void VulkanManager::ShutdownModule()
{
    while (!mResourceStack.empty())
    {
        auto resource = mResourceStack.top();
        resource->DestroyResource();
        mResourceStack.pop();
    }

    glfwTerminate();
}

Render::IMainWindow* VulkanManager::CreateMainWindow(int width, int height, String title)
{
    if (mMainWindow != nullptr)
        return mMainWindow.get();

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mMainWindow = make_shared<GlfwWindow>();
    mMainWindow->SetWH(width, height);
    mMainWindow->SetWindowName(title);
    InitResource(mMainWindow);

    mInstance = make_shared<VulkanInstanceWrapper>();
    InitResource(mInstance);

    mSurface = make_shared<VulkanSurfaceWrapper>();
    InitResource(mSurface);

    mDevice = make_shared<VulkanDeviceWrapper>();
    InitResource(mDevice);

    mRenderPass = make_shared<VulkanRenderPass>();
    InitResource(mRenderPass);

    mSwapChain = make_shared<VulkanSwapChainWrapper>();
    InitResource(mSwapChain);

    mPipeline = make_shared<VulkanGraphicsPipeline>();
    InitResource(mPipeline);

    mSyncObject = make_shared<VulkanSyncWrapper>();
    InitResource(mSyncObject);

    return mMainWindow.get();
}

void VulkanManager::InitResource(std::shared_ptr<IVulkanResource> resource)
{
    if (nullptr == resource)
        return;

    resource->CreateResource();
    mResourceStack.push(resource);
}