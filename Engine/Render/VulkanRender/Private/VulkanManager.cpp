//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindowSystem.h"

using namespace std;

void VulkanManager::StartupModule()
{
    ShutdownModule();

    mMainWindow = make_shared<GlfwWindowSystem>();
    mSystemStack.push_back(mMainWindow);

    mSystemStack.push_back(make_shared<VulkanInstanceSystem>());

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

void VulkanManager::Run()
{
    auto pWindowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (!pWindowComponent || !pWindowComponent->window)
        return;

    mMainWindow->CheckUpdate();

    while (!glfwWindowShouldClose(pWindowComponent->window))
    {
        glfwPollEvents();
        mMainWindow->DrawFrame();
    }

    vkDeviceWaitIdle(VulkanManager::instance()->GetDeviceWrapper()->GetLogicDevice());
}

Render::IMainWindow* VulkanManager::CreateMainWindow(int width, int height, String title)
{
    for (const auto& subSystem : mSystemStack)
        subSystem->OnInit();

    return this;
}

void VulkanManager::ReCreateSwapChain()
{
    auto windowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (!windowComponent || !windowComponent->window)
        return;

    auto window = windowComponent->window;
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
