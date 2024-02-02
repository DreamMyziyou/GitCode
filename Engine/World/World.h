//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WORLD_H
#define WORKENGINE_WORLD_H

#include <entt/entity/registry.hpp>

#include "WorldExport.h"

namespace World
{
    using World = ::entt::registry;

    WORLD_API World* GetWorld();

}  // namespace World

#endif  // WORKENGINE_WORLD_H
