//
// Created by WeslyChen on 2024/1/26.
//
#ifndef WORKENGINE_VULKANGRAPHICSPIPELINE_H
#define WORKENGINE_VULKANGRAPHICSPIPELINE_H

#include "VulkanResource.h"

class VulkanGraphicsPipeline final
{
public:
    VulkanGraphicsPipeline() = default;
    ~VulkanGraphicsPipeline() = default;
    VulkanGraphicsPipeline(const VulkanGraphicsPipeline&) = delete;
    VulkanGraphicsPipeline& operator=(const VulkanGraphicsPipeline&) = delete;
};

#endif  // WORKENGINE_VULKANGRAPHICSPIPELINE_H
