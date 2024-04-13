//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_WORLD_H
#define WORLDENGINE_WORLD_H

#include <entt/entity/registry.hpp>

#include "WorldExport.h"

namespace World
{
    using World = ::entt::registry;

    WORLD_API World* GetWorld();

}  // namespace World

#endif  // WORLDENGINE_WORLD_H
