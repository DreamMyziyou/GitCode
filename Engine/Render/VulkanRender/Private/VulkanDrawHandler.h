//
// Created by WeslyChen on 2024/2/4.
//
#ifndef WORLDENGINE_VULKANDRAWHANDLER_H
#define WORLDENGINE_VULKANDRAWHANDLER_H

#include "VertexBuffer.h"
#include "VulkanResource.h"

class VulkanDrawHandler final
{
public:
    VulkanDrawHandler() = default;
    ~VulkanDrawHandler() = default;
    VulkanDrawHandler(const VulkanDrawHandler&) = delete;
    VulkanDrawHandler& operator=(const VulkanDrawHandler&) = delete;

public:
    void DrawCall();

    void OnWindowResize();
    void OnMeshUpdate(const MeshComponent& mesh);

private:
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
    bool mIsResize = false;
    int mCurrentFrame = 0;

    VertexBuffer mVertexBuffer;
};

#endif  // WORLDENGINE_VULKANDRAWHANDLER_H
