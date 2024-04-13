//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_WORLDMANAGER_H
#define WORLDENGINE_WORLDMANAGER_H

#include "World.h"
#include "Core/ModuleCore/ModuleSingleton.h"

class WorldManager final : ModuleCore::IModule
{
    SINGLETON_MODULE(WorldManager)

public:
    World::World* GetWorldRef() { return &mWorld; }

private:
    World::World mWorld;
};

#endif  // WORLDENGINE_WORLDMANAGER_H
