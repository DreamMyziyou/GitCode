//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANDRAWCALL_H
#define WORKENGINE_VULKANDRAWCALL_H

#include "VulkanResource.h"

class VulkanDrawCall final
{
public:
    VulkanDrawCall() = default;
    ~VulkanDrawCall() = default;
    VulkanDrawCall(const VulkanDrawCall&) = delete;
    VulkanDrawCall& operator=(const VulkanDrawCall&) = delete;

public:
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void Draw();
};

#endif  // WORKENGINE_VULKANDRAWCALL_H
