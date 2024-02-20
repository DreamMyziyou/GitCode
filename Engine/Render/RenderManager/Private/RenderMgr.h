//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_RENDERMGR_H
#define WORKENGINE_RENDERMGR_H

#include "Core/ModuleCore/ModuleSingleton.h"
#include "RenderManager.h"

class RenderMgr final : public ModuleCore::IModule, public RenderManager::IManager
{
    SINGLETON_MODULE(RenderMgr)
};

#endif  // WORKENGINE_RENDERMGR_H
