//
// Created by WeslyChen on 2024/1/26.
//
#ifndef WORKENGINE_VULKANGRAPHICSPIPELINE_H
#define WORKENGINE_VULKANGRAPHICSPIPELINE_H

#include "VulkanResource.h"
#include "VulkanVertexShaderWrapper.h"

class VulkanGraphicsPipeline final : public IVulkanResource
{
public:
    VulkanGraphicsPipeline() = default;
    ~VulkanGraphicsPipeline() override = default;
    VulkanGraphicsPipeline(const VulkanGraphicsPipeline&) = delete;
    VulkanGraphicsPipeline& operator=(const VulkanGraphicsPipeline&) = delete;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    VkPipeline GetPipeline() const { return mPipeline; }

private:
    // Temp for test
    void CreateDefaultShader();

private:
    VkPipelineLayout mPipelineLayout = nullptr;
    VkPipeline mPipeline = nullptr;

    std::shared_ptr<VulkanVertexShaderWrapper> mVertexShader = nullptr;
    std::shared_ptr<VulkanShaderWrapper> mFragShader = nullptr;
};

#endif  // WORKENGINE_VULKANGRAPHICSPIPELINE_H
