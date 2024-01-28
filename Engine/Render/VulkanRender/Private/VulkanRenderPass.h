//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANRENDERPASS_H
#define WORKENGINE_VULKANRENDERPASS_H

#include "VulkanResource.h"

class VulkanRenderPass final : public IVulkanResource
{
public:
    VulkanRenderPass() = default;
    ~VulkanRenderPass() override = default;
    VulkanRenderPass(const VulkanRenderPass&) = delete;
    VulkanRenderPass& operator=(const VulkanRenderPass&) = delete;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    VkRenderPass GetRenderPass() const { return mRenderPass; }

private:
    VkRenderPass mRenderPass = nullptr;
};

#endif  // WORKENGINE_VULKANRENDERPASS_H
