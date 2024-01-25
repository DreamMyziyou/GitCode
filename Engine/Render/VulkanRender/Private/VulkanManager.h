//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>

#include "GlfwWindow.h"
#include "Module/ModuleCore/ModuleSingleton.h"
#include "VulkanDeviceWrapper.h"
#include "VulkanInstanceWrapper.h"
#include "VulkanRender.h"
#include "VulkanSwapChainWrapper.h"

class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager, public IVulkanResource
{
    SINGLETON_MODULE(VulkanManager)

public:
    VkInstance GetVulkanInstance() const override { return mInstance.GetVulkanInstance(); }
    GLFWwindow* GetWindowHandle() const override { return mMainWindow.GetWindow(); }
    VkSurfaceKHR GetSurface() const override { return mSurface; }
    VkPhysicalDevice GetPhysicalDevice() const override { return mDevice.GetPhysicalDevice(); }
    VkDevice GetVulkanDevice() const override { return mDevice.GetLogicDevice(); }
    VkQueue GetGraphicsQueue() const override { return mDevice.GetGraphicsQueue(); }
    VkSwapchainKHR GetSwapChain() const override { return mSwapChain.GetSwapChain(); }

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    Render::IMainWindow* CreateMainWindow(int width, int height, String title);

private:
    void InitGlfw();
    void TerminalGlfw();

    void CreateSurface();
    void DestroySurface();

private:
    GlfwWindow mMainWindow;
    VulkanInstanceWrapper mInstance;
    VkSurfaceKHR mSurface = nullptr;
    VulkanDeviceWrapper mDevice;
    VulkanSwapChainWrapper mSwapChain;
};

#endif  // WORKENGINE_VULKANMANAGER_H
