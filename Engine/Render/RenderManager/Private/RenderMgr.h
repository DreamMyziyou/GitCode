//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_RENDERMGR_H
#define WORLDENGINE_RENDERMGR_H

#include "Core/ModuleCore/ModuleSingleton.h"
#include "RenderManager.h"

class RenderMgr final : public ModuleCore::IModule, public RenderManager::IManager
{
    SINGLETON_MODULE(RenderMgr)
};

#endif  // WORLDENGINE_RENDERMGR_H
