//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindowSystem.h"
#include "VulkanComponent.h"

using namespace std;

void VulkanManager::StartupModule()
{
    ShutdownModule();

    mMainWindow = make_shared<GlfwWindowSystem>();
    mSystemStack.push_back(mMainWindow);

    mSystemStack.push_back(make_shared<VulkanInstanceSystem>());
    mSystemStack.push_back(make_shared<VulkanSurfaceSystem>());
    mSystemStack.push_back(make_shared<VulkanDeviceSystem>());

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
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mLogicDevice)
        return;

    mMainWindow->CheckUpdate();

    while (!glfwWindowShouldClose(pWindowComponent->window))
    {
        glfwPollEvents();
        mMainWindow->DrawFrame();
    }

    vkDeviceWaitIdle(deviceComponent->mLogicDevice);
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
    auto surfaceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>();
    if (!surfaceComponent)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    auto window = windowComponent->window;
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(deviceComponent->mLogicDevice);

    surfaceComponent->update(deviceComponent->mPhysicalDevice);
    mSwapChain->OnDestroy();
    mSwapChain->OnInit();
}
