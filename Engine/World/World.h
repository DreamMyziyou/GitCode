//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WORLD_H
#define WORKENGINE_WORLD_H

#include "WORLDExport.h"
#include "entt/src/entt/entity/registry.hpp"

namespace World
{
    using World = ::entt::registry;

    WORLD_API World* GetWorld();

}  // namespace WORLD

#endif  // WORKENGINE_WORLD_H
