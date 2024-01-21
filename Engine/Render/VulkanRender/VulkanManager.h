//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>

#include "Module/ModuleCore/ModuleSingleton.h"
#include "Render/RenderInterface/IWindow.h"
#include "VulkanRender.h"

class VulkanManagerImpl;
class VULKANRENDER_API VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    std::shared_ptr<Render::IWindow> CreateGlfwWindow();

private:
    VulkanManagerImpl* mImpl = nullptr;
};

#endif  // WORKENGINE_VULKANMANAGER_H
