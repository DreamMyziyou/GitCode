//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_RENDERMGR_H
#define WORKENGINE_RENDERMGR_H

#include "Module/ModuleCore/ModuleSingleton.h"
#include "RenderManager.h"

class RenderMgr final : public ModuleCore::IModule, public RenderManager::IManager
{
    SINGLETON_MODULE(RenderMgr)

public:
    std::shared_ptr<Render::IWindow> CreateWindow() override;
};

#endif  // WORKENGINE_RENDERMGR_H
