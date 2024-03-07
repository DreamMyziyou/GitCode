//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>
#include <vector>

#include "Core/ModuleCore/ModuleSingleton.h"
#include "GlfwWindowSystem.h"
#include "VulkanDeviceWrapper.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanInstanceWrapper.h"
#include "VulkanRender.h"
#include "VulkanRenderPass.h"
#include "VulkanSurfaceWrapper.h"
#include "VulkanSwapChainWrapper.h"

class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    VkInstance GetVulkanInstance() const { return mInstance->GetVulkanInstance(); }
    VkDevice GetDevice() const { return mDevice->GetLogicDevice(); }
    VkRenderPass GetRenderPass() const { return mRenderPass->GetRenderPass(); }
    std::shared_ptr<VulkanSurfaceWrapper> GetSurfaceWrapper() const { return mSurface; }
    std::shared_ptr<VulkanDeviceWrapper> GetDeviceWrapper() const { return mDevice; }
    std::shared_ptr<VulkanGraphicsPipeline> GetPipelineWrapper() const { return mPipeline; }
    std::shared_ptr<VulkanSwapChainWrapper> GetSwapChainWrapper() const { return mSwapChain; }

    Render::IMainWindow* CreateMainWindow(int width, int height, String title);

    void ReCreateSwapChain();

private:
    std::vector<std::shared_ptr<IVulkanSubSystem>> mSystemStack;

    std::shared_ptr<GlfwWindowSystem> mMainWindow = nullptr;
    std::shared_ptr<VulkanInstanceWrapper> mInstance = nullptr;
    std::shared_ptr<VulkanSurfaceWrapper> mSurface = nullptr;
    std::shared_ptr<VulkanDeviceWrapper> mDevice = nullptr;
    std::shared_ptr<VulkanRenderPass> mRenderPass = nullptr;
    std::shared_ptr<VulkanGraphicsPipeline> mPipeline = nullptr;
    std::shared_ptr<VulkanSwapChainWrapper> mSwapChain = nullptr;
};

#endif  // WORKENGINE_VULKANMANAGER_H
