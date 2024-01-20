//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_ECS_H
#define WORKENGINE_ECS_H

#include "ECSExport.h"
#include <entt/entity/registry.hpp>

namespace ECS
{
    using World = ::entt::registry;

    ECS_API World* GetWorld();

};  // namespace ECS

#endif  // WORKENGINE_ECS_H
