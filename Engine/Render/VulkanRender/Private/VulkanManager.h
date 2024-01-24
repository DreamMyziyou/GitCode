//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>

#include "GlfwWindow.h"
#include "Module/ModuleCore/ModuleSingleton.h"
#include "VulkanDeviceSwapChainWrapper.h"
#include "VulkanInstanceWrapper.h"
#include "VulkanRender.h"

class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    VkInstance GetVulkanInstance() const { return mInstance.GetVulkanInstance(); }
    GLFWwindow* GetWindowHandle() const { return mMainWindow.GetWindow(); }
    VkSurfaceKHR GetSurface() const { return mSurface; }
    VkPhysicalDevice GetPhysicalDevice() const { return mDevice.GetPhysicalDevice(); }
    VkDevice GetVulkanDevice() const { return mDevice.GetLogicDevice(); }
    VkQueue GetGraphicsQueue() const { return mDevice.GetGraphicsQueue(); }
    VkSwapchainKHR GetSwapChain() const { return mDevice.GetSwapChain(); }

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
    VulkanDeviceSwapChainWrapper mDevice;
};

#endif  // WORKENGINE_VULKANMANAGER_H
