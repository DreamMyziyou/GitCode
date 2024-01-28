//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>
#include <stack>

#include "GlfwWindow.h"
#include "Module/ModuleCore/ModuleSingleton.h"
#include "VulkanDeviceWrapper.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanInstanceWrapper.h"
#include "VulkanRender.h"
#include "VulkanRenderPass.h"
#include "VulkanSurfaceWrapper.h"
#include "VulkanSwapChainWrapper.h"
#include "VulkanSyncWrapper.h"

class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    VkInstance GetVulkanInstance() const { return mInstance->GetVulkanInstance(); }
    GLFWwindow* GetWindowHandle() const { return mMainWindow->GetWindow(); }
    VkSurfaceKHR GetSurface() const { return mSurface->GetSurface(); }
    VkPhysicalDevice GetPhysicalDevice() const { return mDevice->GetPhysicalDevice(); }
    VkDevice GetVulkanDevice() const { return mDevice->GetLogicDevice(); }
    VkQueue GetGraphicsQueue() const { return mDevice->GetGraphicsQueue(); }
    VkFormat GetSwapChainFormat() const { return mDevice->GetExpectSurfaceFormat().format; }
    VkExtent2D GetSwapChainExtent() const { return mDevice->GetExpectSwapChainExtent(); }
    VkRenderPass GetRenderPass() const { return mRenderPass->GetRenderPass(); }
    VkSwapchainKHR GetSwapChain() const { return mSwapChain->GetSwapChain(); }

    Render::IMainWindow* CreateMainWindow(int width, int height, String title);
    std::shared_ptr<VulkanDeviceWrapper> GetDeviceWrapper() const { return mDevice; }
    std::shared_ptr<VulkanRenderPass> GetRenderPassWrapper() const { return mRenderPass; }
    std::shared_ptr<VulkanSwapChainWrapper> GetSwapChainWrapper() const { return mSwapChain; }
    std::shared_ptr<VulkanGraphicsPipeline> GetPipelineWrapper() const { return mPipeline; }
    std::shared_ptr<VulkanSyncWrapper> GetSyncObject() const { return mSyncObject; }

private:
    void InitResource(std::shared_ptr<IVulkanResource> resource);

private:
    std::stack<std::shared_ptr<IVulkanResource>> mResourceStack;

    std::shared_ptr<GlfwWindow> mMainWindow = nullptr;
    std::shared_ptr<VulkanInstanceWrapper> mInstance = nullptr;
    std::shared_ptr<VulkanSurfaceWrapper> mSurface = nullptr;
    std::shared_ptr<VulkanDeviceWrapper> mDevice = nullptr;
    std::shared_ptr<VulkanRenderPass> mRenderPass = nullptr;
    std::shared_ptr<VulkanSwapChainWrapper> mSwapChain = nullptr;
    std::shared_ptr<VulkanGraphicsPipeline> mPipeline = nullptr;
    std::shared_ptr<VulkanSyncWrapper> mSyncObject = nullptr;
};

#endif  // WORKENGINE_VULKANMANAGER_H
