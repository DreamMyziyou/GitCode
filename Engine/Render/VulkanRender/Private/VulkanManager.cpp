//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManager.h"

#include "GlfwWindowSystem.h"
#include "VulkanComponent.h"
#include "VulkanDeviceSystem.h"
#include "VulkanGraphicsPipelineSystem.h"
#include "VulkanInstanceSystem.h"
#include "VulkanRenderPassSystem.h"
#include "VulkanSurfaceSystem.h"

using namespace std;

void VulkanManager::StartupModule()
{
    ShutdownModule();

    mMainWindow = make_shared<GlfwWindowSystem>();
    mSystemStack.push_back(mMainWindow);

    mSystemStack.push_back(make_shared<VulkanInstanceSystem>());
    mSystemStack.push_back(make_shared<VulkanSurfaceSystem>());
    mSystemStack.push_back(make_shared<VulkanDeviceSystem>());
    mSystemStack.push_back(make_shared<VulkanRenderPassSystem>());
    mSystemStack.push_back(make_shared<VulkanGraphicsPipelineSystem>());

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
    for (const auto& system : mSystemStack)
        system->OnUpdate();
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
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    auto window = windowComponent->window;
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(deviceComponent->logicDevice);

    surfaceComponent->update(deviceComponent->physicalDevice);
    mSwapChain->OnDestroy();
    mSwapChain->OnInit();
}
