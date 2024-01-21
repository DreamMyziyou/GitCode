//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_ENGINEMANAGER_H
#define WORKENGINE_ENGINEMANAGER_H

#include "Engine.h"
#include "Module/ModuleCore/ModuleSingleton.h"

class EngineManager final : public ModuleCore::IModule, public Engine::IEngine
{
    SINGLETON_MODULE(EngineManager)
};

#endif  // WORKENGINE_ENGINEMANAGER_H
