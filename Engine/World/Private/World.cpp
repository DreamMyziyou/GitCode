//
// Created by WeslyChen on 2024/1/20.
//

#include "World.h"

#include "WorldManager.h"

World::World* World::GetWorld()
{
    return WorldManager::instance()->GetWorldRef();
}
