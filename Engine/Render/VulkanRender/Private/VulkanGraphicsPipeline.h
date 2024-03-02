//
// Created by WeslyChen on 2024/1/26.
//
#ifndef WORKENGINE_VULKANGRAPHICSPIPELINE_H
#define WORKENGINE_VULKANGRAPHICSPIPELINE_H

#include "ShaderBuffer.h"
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

    void DrawCall();

    void OnMeshUpdate(const MeshComponent& mesh);

private:
    void CreateDefaultShader();
    void CreateDescriptorPool();
    void CreateDescriptorSets();
    void CreateDescriptorSetLayout();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void UpdateUniformBuffer(uint32_t currentImage);

private:
    VkDescriptorPool mDescriptorPool = nullptr;
    VkDescriptorSetLayout mDescriptorSetLayout = nullptr;
    std::vector<VkDescriptorSet> mDescriptorSets;
    VkPipelineLayout mPipelineLayout = nullptr;
    VkPipeline mPipeline = nullptr;

    std::unique_ptr<ShaderBuffer> mShaderBuffer = nullptr;
    std::shared_ptr<VulkanVertexShaderWrapper> mVertexShader = nullptr;
    std::shared_ptr<VulkanShaderWrapper> mFragShader = nullptr;

    int mCurrentFrame = 0;
};

#endif  // WORKENGINE_VULKANGRAPHICSPIPELINE_H
