//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANSURFACESYSTEM_H
#define WORKENGINE_VULKANSURFACESYSTEM_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanSurfaceSystem final : public IVulkanSubSystem
{
public:
    VulkanSurfaceSystem() = default;
    ~VulkanSurfaceSystem() override = default;
    VulkanSurfaceSystem(const VulkanSurfaceSystem&) = delete;
    VulkanSurfaceSystem& operator=(const VulkanSurfaceSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;
};

#endif  // WORKENGINE_VULKANSURFACESYSTEM_H
