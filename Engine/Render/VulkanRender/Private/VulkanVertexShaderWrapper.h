//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANVERTEXSHADERWRAPPER_H
#define WORKENGINE_VULKANVERTEXSHADERWRAPPER_H

#include <array>

#include "VulkanShaderWrapper.h"

class VulkanVertexShaderWrapper final : public VulkanShaderWrapper
{
public:
    VulkanVertexShaderWrapper();
    ~VulkanVertexShaderWrapper() override = default;
    VulkanVertexShaderWrapper(const VulkanVertexShaderWrapper&) = delete;
    VulkanVertexShaderWrapper& operator=(const VulkanVertexShaderWrapper&) = delete;

public:
    void OnInit() override;

public:
    const VkPipelineVertexInputStateCreateInfo& GetVertexInputInfo() const { return mVertexInputCreateInfo; }
    const VkPipelineInputAssemblyStateCreateInfo& GetInputAssemblyInfo() const { return mInputAssembly; }

private:
    VkVertexInputBindingDescription mBindingDescription;
    std::array<VkVertexInputAttributeDescription, 2> mAttributeDescriptions;
    VkPipelineVertexInputStateCreateInfo mVertexInputCreateInfo;
    VkPipelineInputAssemblyStateCreateInfo mInputAssembly;
};

#endif  // WORKENGINE_VULKANVERTEXSHADERWRAPPER_H
