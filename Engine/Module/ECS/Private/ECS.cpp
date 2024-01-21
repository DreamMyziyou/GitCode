//
// Created by WeslyChen on 2024/1/20.
//

#include "ECS.h"

#include "WorldManager.h"

ECS::World* ECS::GetWorld()
{
    return WorldManager::instance()->GetWorldRef();
}
