//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanVertexShaderWrapper.h"

#include "GeometryToVulkan.h"

VulkanVertexShaderWrapper::VulkanVertexShaderWrapper()
{
    mType = VK_SHADER_STAGE_VERTEX_BIT;
}

void VulkanVertexShaderWrapper::OnInit()
{
    if (mShader)
        return;

    VulkanShaderWrapper::OnInit();

    mBindingDescription = GeometryToVulkan::GetVertexBindingDescription();
    mAttributeDescriptions = GeometryToVulkan::GetVertexAttributeDescriptions();

    mVertexInputCreateInfo = {};
    mVertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    mVertexInputCreateInfo.vertexBindingDescriptionCount = 1;
    mVertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(mAttributeDescriptions.size());
    mVertexInputCreateInfo.pVertexBindingDescriptions = &mBindingDescription;
    mVertexInputCreateInfo.pVertexAttributeDescriptions = mAttributeDescriptions.data();

    mInputAssembly = {};
    mInputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    mInputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    mInputAssembly.primitiveRestartEnable = VK_FALSE;
}
