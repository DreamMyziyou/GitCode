//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

using namespace std;

void VulkanManager::StartupModule()
{
    ShutdownModule();

    mMainWindow = make_shared<GlfwWindowSystem>();
    mSystemStack.push_back(mMainWindow);

    mInstance = make_shared<VulkanInstanceWrapper>();
    mSystemStack.push_back(mInstance);

    mSurface = make_shared<VulkanSurfaceWrapper>();
    mSystemStack.push_back(mSurface);

    mDevice = make_shared<VulkanDeviceWrapper>();
    mSystemStack.push_back(mDevice);

    mRenderPass = make_shared<VulkanRenderPass>();
    mSystemStack.push_back(mRenderPass);

    mPipeline = make_shared<VulkanGraphicsPipeline>();
    mSystemStack.push_back(mPipeline);

    mSwapChain = make_shared<VulkanSwapChainWrapper>();
    mSystemStack.push_back(mSwapChain);
}

void VulkanManager::ShutdownModule()
{
    while (!mSystemStack.empty())
    {
        auto resource = mSystemStack.back();
        resource->OnDestroy();
        mSystemStack.pop_back();
    }

    mMainWindow = nullptr;
}

Render::IMainWindow* VulkanManager::CreateMainWindow(int width, int height, String title)
{
    for (const auto& subSystem : mSystemStack)
        subSystem->OnInit();

    return mMainWindow.get();
}

void VulkanManager::ReCreateSwapChain()
{
    if (nullptr == VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>())
        return;

    auto window = mMainWindow->QueryGlfwWindowHandle();
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(GetDevice());

    mSurface->OnUpdate(mDevice->GetPhysicalDevice());
    mSwapChain->OnDestroy();
    mSwapChain->OnInit();
}
