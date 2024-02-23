//
// Created by WeslyChen on 2024/2/23.
//
#ifndef WORLDENGINE_VULKANRESOURCECENTER_H
#define WORLDENGINE_VULKANRESOURCECENTER_H

#include "Core/World/World.h"
#include "VulkanResource.h"

class VulkanResourceCenter final
{
    SINGLETON_CLASS(VulkanResourceCenter)

    entt::registry world;
};

#endif  // WORLDENGINE_VULKANRESOURCECENTER_H
