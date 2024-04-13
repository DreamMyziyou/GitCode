//
// Created by WeslyChen on 2024/4/13.
//
#ifndef WORLDENGINE_PIPELINECOMPONENT_H
#define WORLDENGINE_PIPELINECOMPONENT_H

struct PipelineComponent
{
    VkDescriptorPool mDescriptorPool = nullptr;
    VkDescriptorSetLayout mDescriptorSetLayout = nullptr;
    std::vector<VkDescriptorSet> mDescriptorSets;
    VkPipelineLayout mPipelineLayout = nullptr;
    VkPipeline mPipeline = nullptr;
};

#endif  // WORLDENGINE_PIPELINECOMPONENT_H
