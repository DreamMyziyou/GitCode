//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindowSystem.h"

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

    mMainWindow = nullptr;
}

Render::IMainWindow* VulkanManager::CreateMainWindow(int width, int height, String title)
{
    if (mMainWindow != nullptr)
        return mMainWindow.get();

    mMainWindow = make_shared<GlfwWindow>();

    mInstance = make_shared<VulkanInstanceWrapper>();
    InitResource(mInstance);

    mSurface = make_shared<VulkanSurfaceWrapper>();
    InitResource(mSurface);

    mDevice = make_shared<VulkanDeviceWrapper>();
    InitResource(mDevice);

    mRenderPass = make_shared<VulkanRenderPass>();
    InitResource(mRenderPass);

    mPipeline = make_shared<VulkanGraphicsPipeline>();
    InitResource(mPipeline);

    mSwapChain = make_shared<VulkanSwapChainWrapper>();
    InitResource(mSwapChain);

    return mMainWindow.get();
}

void VulkanManager::ReCreateSwapChain()
{
    auto window = GlfwWindowSystem::QueryGlfwWindowHandle();
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(GetDevice());

    mSurface->OnUpdate(mDevice->GetPhysicalDevice());
    mSwapChain->DestroyResource();
    mSwapChain->CreateResource();
}

void VulkanManager::InitResource(std::shared_ptr<IVulkanResource> resource)
{
    if (nullptr == resource)
        return;

    resource->CreateResource();
    mResourceStack.push(resource);
}
