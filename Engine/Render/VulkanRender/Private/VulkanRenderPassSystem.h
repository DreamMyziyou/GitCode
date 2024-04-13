//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORLDENGINE_VULKANRENDERPASSSYSTEM_H
#define WORLDENGINE_VULKANRENDERPASSSYSTEM_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanRenderPassSystem final : public IVulkanSubSystem
{
public:
    VulkanRenderPassSystem() = default;
    ~VulkanRenderPassSystem() override = default;
    VulkanRenderPassSystem(const VulkanRenderPassSystem&) = delete;
    VulkanRenderPassSystem& operator=(const VulkanRenderPassSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;
};

#endif  // WORLDENGINE_VULKANRENDERPASSSYSTEM_H
