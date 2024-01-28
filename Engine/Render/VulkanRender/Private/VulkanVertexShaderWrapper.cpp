//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanVertexShaderWrapper.h"

VulkanVertexShaderWrapper::VulkanVertexShaderWrapper()
{
    mType = VK_SHADER_STAGE_VERTEX_BIT;
}

void VulkanVertexShaderWrapper::CreateResource()
{
    if (mShader)
        return;

    VulkanShaderWrapper::CreateResource();

    mVertexInputCreateInfo = {};
    mVertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    mVertexInputCreateInfo.vertexBindingDescriptionCount = 0;
    mVertexInputCreateInfo.pVertexBindingDescriptions = nullptr;  // Optional
    mVertexInputCreateInfo.vertexAttributeDescriptionCount = 0;
    mVertexInputCreateInfo.pVertexAttributeDescriptions = nullptr;  // Optional

    mInputAssembly = {};
    mInputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    mInputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    mInputAssembly.primitiveRestartEnable = VK_FALSE;
}
