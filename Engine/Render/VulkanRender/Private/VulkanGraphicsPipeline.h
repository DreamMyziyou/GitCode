//
// Created by WeslyChen on 2024/1/26.
//
#ifndef WORKENGINE_VULKANGRAPHICSPIPELINE_H
#define WORKENGINE_VULKANGRAPHICSPIPELINE_H

#include "VertexBuffer.h"
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

    void OnWindowResize();
    void OnMeshUpdate(const MeshComponent& mesh);

private:
    // Temp for test
    void CreateDefaultShader();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
    VkPipelineLayout mPipelineLayout = nullptr;
    VkPipeline mPipeline = nullptr;

    std::shared_ptr<VulkanVertexShaderWrapper> mVertexShader = nullptr;
    std::shared_ptr<VulkanShaderWrapper> mFragShader = nullptr;

    bool mIsResize = false;
    int mCurrentFrame = 0;

    std::unique_ptr<VertexBuffer> mVertexBuffer = nullptr;
};

#endif  // WORKENGINE_VULKANGRAPHICSPIPELINE_H
