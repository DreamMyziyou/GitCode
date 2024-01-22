//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGER_H
#define WORKENGINE_VULKANMANAGER_H

#include <memory>

#include "Module/ModuleCore/ModuleSingleton.h"
#include "VulkanRender.h"

class VulkanManagerImpl;
class VulkanManager final : public ModuleCore::IModule, public VulkanRender::IManager
{
    SINGLETON_MODULE(VulkanManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    Render::IMainWindow* GetMainWindow() const;

private:
    VulkanManagerImpl* mImpl = nullptr;
};

#endif  // WORKENGINE_VULKANMANAGER_H
