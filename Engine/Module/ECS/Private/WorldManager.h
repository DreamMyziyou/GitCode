//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WORLDMANAGER_H
#define WORKENGINE_WORLDMANAGER_H

#include "ECS.h"
#include "Module/ModuleCore/ModuleSingleton.h"

class WorldManager final : ModuleCore::IModule
{
    SINGLETON_MODULE(WorldManager)

public:
    ECS::World* GetWorldRef() { return &mWorld; }

private:
    ECS::World mWorld;
};

#endif  // WORKENGINE_WORLDMANAGER_H
