//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WORLDMANAGER_H
#define WORKENGINE_WORLDMANAGER_H

#include "World.h"
#include "Module/ModuleCore/ModuleSingleton.h"

class WorldManager final : ModuleCore::IModule
{
    SINGLETON_MODULE(WorldManager)

public:
    World::World* GetWorldRef() { return &mWorld; }

private:
    World::World mWorld;
};

#endif  // WORKENGINE_WORLDMANAGER_H
