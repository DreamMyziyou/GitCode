//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANMANAGER_H
#define WORLDENGINE_VULKANMANAGER_H

#include <memory>
#include <vector>

#include "Core/ModuleCore/ModuleSingleton.h"
#include "VulkanRender.h"
#include "VulkanSwapChainWrapper.h"

class GlfwWindowSystem;
class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager, public Render::IMainWindow
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    void Run() override;

public:
    std::shared_ptr<VulkanSwapChainWrapper> GetSwapChainWrapper() const { return mSwapChain; }

    Render::IMainWindow* CreateMainWindow(int width, int height, String title);

    void ReCreateSwapChain();

private:
    std::vector<std::shared_ptr<IVulkanSubSystem>> mSystemStack{};

    std::shared_ptr<GlfwWindowSystem> mMainWindow = nullptr;
    std::shared_ptr<VulkanSwapChainWrapper> mSwapChain = nullptr;
};

#endif  // WORLDENGINE_VULKANMANAGER_H
