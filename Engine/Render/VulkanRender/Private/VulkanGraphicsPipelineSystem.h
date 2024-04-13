//
// Created by WeslyChen on 2024/1/26.
//
#ifndef WORLDENGINE_VULKANGRAPHICSPIPELINESYSTEM_H
#define WORLDENGINE_VULKANGRAPHICSPIPELINESYSTEM_H

#include "ShaderBuffer.h"
#include "VkRCenter.h"
#include "VulkanVertexShaderWrapper.h"

class VulkanGraphicsPipelineSystem final : public IVulkanSubSystem
{
public:
    VulkanGraphicsPipelineSystem() = default;
    ~VulkanGraphicsPipelineSystem() override = default;
    VulkanGraphicsPipelineSystem(const VulkanGraphicsPipelineSystem&) = delete;
    VulkanGraphicsPipelineSystem& operator=(const VulkanGraphicsPipelineSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
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
    std::unique_ptr<ShaderBuffer> mShaderBuffer = nullptr;
    std::shared_ptr<VulkanVertexShaderWrapper> mVertexShader = nullptr;
    std::shared_ptr<VulkanShaderWrapper> mFragShader = nullptr;

    int mCurrentFrame = 0;
};

#endif  // WORLDENGINE_VULKANGRAPHICSPIPELINESYSTEM_H
