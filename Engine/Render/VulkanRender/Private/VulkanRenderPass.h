//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORLDENGINE_VULKANRENDERPASS_H
#define WORLDENGINE_VULKANRENDERPASS_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanRenderPass final : public IVulkanSubSystem
{
public:
    VulkanRenderPass() = default;
    ~VulkanRenderPass() override = default;
    VulkanRenderPass(const VulkanRenderPass&) = delete;
    VulkanRenderPass& operator=(const VulkanRenderPass&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    VkRenderPass GetRenderPass() const { return mRenderPass; }

private:
    VkRenderPass mRenderPass = nullptr;
};

#endif  // WORLDENGINE_VULKANRENDERPASS_H
