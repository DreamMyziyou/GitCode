//
// Created by WeslyChen on 2024/1/26.
//
#include "VulkanGraphicsPipeline.h"

#include "VulkanManager.h"

using namespace std;

void VulkanGraphicsPipeline::CreateResource()
{
    std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    auto swapChainExtent = VulkanManager::instance()->GetSwapChainExtent();

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapChainExtent.width;
    viewport.height = (float)swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;  // Optional
    rasterizer.depthBiasClamp = 0.0f;  // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f;  // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;  // Optional
    multisampling.pSampleMask = nullptr;  // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE;  // Optional
    multisampling.alphaToOneEnable = VK_FALSE;  // Optional

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;  // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;  // Optional

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;  // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;  // Optional
    colorBlending.blendConstants[1] = 0.0f;  // Optional
    colorBlending.blendConstants[2] = 0.0f;  // Optional
    colorBlending.blendConstants[3] = 0.0f;  // Optional

    VkPipelineLayout pipelineLayout;
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;  // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr;  // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0;  // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr;  // Optional

    auto vkResult = vkCreatePipelineLayout(VulkanManager::instance()->GetVulkanDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout);
    if (vkResult != VK_SUCCESS)
        return;

    mPipelineLayout = pipelineLayout;

    CreateDefaultShader();
    VkPipelineShaderStageCreateInfo shaderStages[] = {mVertexShader->GetShaderCreateInfo(), mFragShader->GetShaderCreateInfo()};

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &mVertexShader->GetVertexInputInfo();
    pipelineInfo.pInputAssemblyState = &mVertexShader->GetInputAssemblyInfo();
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr;  // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.renderPass = VulkanManager::instance()->GetRenderPass();
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;  // Optional
    pipelineInfo.basePipelineIndex = -1;  // Optional

    VkPipeline graphicsPipeline;
    vkResult = vkCreateGraphicsPipelines(VulkanManager::instance()->GetVulkanDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
    if (vkResult != VK_SUCCESS)
        return;
    mPipeline = graphicsPipeline;
}

void VulkanGraphicsPipeline::DestroyResource()
{
    if (nullptr == mPipelineLayout)
        return;

    vkDestroyPipeline(VulkanManager::instance()->GetVulkanDevice(), mPipeline, nullptr);

    if (mVertexShader)
    {
        mVertexShader->DestroyResource();
        mVertexShader = nullptr;
    }

    if (mFragShader)
    {
        mFragShader->DestroyResource();
        mFragShader = nullptr;
    }

    vkDestroyPipelineLayout(VulkanManager::instance()->GetVulkanDevice(), mPipelineLayout, nullptr);
    mPipelineLayout = nullptr;
}

void VulkanGraphicsPipeline::CreateDefaultShader()
{
    mVertexShader = make_shared<VulkanVertexShaderWrapper>();
    mVertexShader->SetShaderPath("Shader/HelloTriangle.vert.spv");
    mVertexShader->CreateResource();

    mFragShader = make_shared<VulkanShaderWrapper>();
    mFragShader->SetShaderType(VK_SHADER_STAGE_FRAGMENT_BIT);
    mFragShader->SetShaderPath("Shader/Base.frag.spv");
    mFragShader->CreateResource();
}
