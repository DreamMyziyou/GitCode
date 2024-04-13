//
// Created by WeslyChen on 2024/1/26.
//
#include "VulkanGraphicsPipelineSystem.h"

#include <chrono>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GlfwWindowComponent.h"
#include "PipelineComponent.h"
#include "UniformBuffer.h"
#include "VulkanComponent.h"
#include "VulkanManager.h"

using namespace std;

void VulkanGraphicsPipelineSystem::OnInit()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;
    auto renderPassComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanRenderPassComponent>();
    if (!renderPassComponent)
        return;
    if (VkRCenter::instance()->activePipelineEntity != entt::null)
        return;

    auto& pipelineEntity = VkRCenter::instance()->activePipelineEntity;
    pipelineEntity = VkRCenter::instance()->world.create();
    auto& pipelineComponent = VkRCenter::instance()->world.emplace<PipelineComponent>(pipelineEntity);

    mShaderBuffer = make_unique<ShaderBuffer>();
    CreateDefaultShader();
    CreateDescriptorPool();
    CreateDescriptorSetLayout();
    CreateDescriptorSets();

    std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    auto swapChainExtent = VkRCenter::instance()->GetComponentFromVulkan<VulkanSurfaceComponent>()->expectSwapChainExtent;

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
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
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
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &pipelineComponent.mDescriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0;  // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr;  // Optional

    auto vkResult = vkCreatePipelineLayout(deviceComponent->logicDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout);
    if (vkResult != VK_SUCCESS)
        return;

    pipelineComponent.mPipelineLayout = pipelineLayout;

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
    pipelineInfo.renderPass = renderPassComponent->renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;  // Optional
    pipelineInfo.basePipelineIndex = -1;  // Optional

    VkPipeline graphicsPipeline;
    vkResult = vkCreateGraphicsPipelines(deviceComponent->logicDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
    if (vkResult != VK_SUCCESS)
        return;
    pipelineComponent.mPipeline = graphicsPipeline;
}

void VulkanGraphicsPipelineSystem::OnDestroy()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;
    if (VkRCenter::instance()->activePipelineEntity == entt::null)
        return;
    auto pipelineComponent = VkRCenter::instance()->GetComponentFromActivePipeline<PipelineComponent>();
    if (!pipelineComponent)
        return;

    if (pipelineComponent->mPipeline)
    {
        vkDestroyPipeline(deviceComponent->logicDevice, pipelineComponent->mPipeline, nullptr);
        pipelineComponent->mPipeline = nullptr;
    }

    if (mVertexShader)
    {
        mVertexShader->OnDestroy();
        mVertexShader = nullptr;
    }

    if (mFragShader)
    {
        mFragShader->OnDestroy();
        mFragShader = nullptr;
    }

    if (pipelineComponent->mPipelineLayout)
    {
        vkDestroyPipelineLayout(deviceComponent->logicDevice, pipelineComponent->mPipelineLayout, nullptr);
        pipelineComponent->mPipelineLayout = nullptr;
    }

    if (pipelineComponent->mDescriptorPool)
    {
        vkDestroyDescriptorPool(deviceComponent->logicDevice, pipelineComponent->mDescriptorPool, nullptr);
        pipelineComponent->mDescriptorPool = nullptr;
    }

    if (pipelineComponent->mDescriptorSetLayout)
    {
        vkDestroyDescriptorSetLayout(deviceComponent->logicDevice, pipelineComponent->mDescriptorSetLayout, nullptr);
        pipelineComponent->mDescriptorSetLayout = nullptr;
    }

    mShaderBuffer = nullptr;

    VkRCenter::instance()->world.destroy(VkRCenter::instance()->activePipelineEntity);
    VkRCenter::instance()->activePipelineEntity = entt::null;
}

void VulkanGraphicsPipelineSystem::OnUpdate()
{
    auto world = World::GetWorld();
    auto positionView = world->view<MeshComponent>();
    for (const auto& [entityKey, mesh] : positionView.each())
    {
        // test
        OnMeshUpdate(mesh);
        mesh.dirty = false;
        break;
    }

    auto pWindowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (!pWindowComponent || !pWindowComponent->window)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->logicDevice)
        return;

    while (!glfwWindowShouldClose(pWindowComponent->window))
    {
        glfwPollEvents();
        DrawCall();
    }

    vkDeviceWaitIdle(deviceComponent->logicDevice);
}

void VulkanGraphicsPipelineSystem::DrawCall()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    auto commandBuffer = deviceComponent->commandBuffers[mCurrentFrame];
    auto inFlightFence = deviceComponent->inFlightFences[mCurrentFrame];
    auto imageAvailableSemaphore = deviceComponent->imageAvailableSemaphores[mCurrentFrame];
    auto renderFinishedSemaphore = deviceComponent->renderFinishedSemaphores[mCurrentFrame];
    auto swapChain = VulkanManager::instance()->GetSwapChainWrapper()->GetSwapChain();

    vkWaitForFences(deviceComponent->logicDevice, 1, &inFlightFence, VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result =
            vkAcquireNextImageKHR(deviceComponent->logicDevice, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        VulkanManager::instance()->ReCreateSwapChain();
        return;
    }

    UpdateUniformBuffer(mCurrentFrame);

    vkResetFences(deviceComponent->logicDevice, 1, &inFlightFence);

    vkResetCommandBuffer(commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
    RecordCommandBuffer(commandBuffer, imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;
    if (vkQueueSubmit(deviceComponent->graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS)
        return;

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    result = vkQueuePresentKHR(deviceComponent->presentQueue, &presentInfo);

    auto view = VkRCenter::instance()->world.view<WindowResizeComponent>();
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || !view.empty())
    {
        for (const auto& entity : view)
            VkRCenter::instance()->world.remove<WindowResizeComponent>(entity);
        VulkanManager::instance()->ReCreateSwapChain();
        return;
    }

    mCurrentFrame = (mCurrentFrame + 1) % VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT;
}

void VulkanGraphicsPipelineSystem::OnMeshUpdate(const MeshComponent& mesh)
{
    if (!mShaderBuffer)
        return;
    if (!mesh.dirty)
        return;

    mShaderBuffer->OnMeshUpdate(mesh);
}

void VulkanGraphicsPipelineSystem::CreateDefaultShader()
{
    mVertexShader = make_shared<VulkanVertexShaderWrapper>();
    mVertexShader->SetShaderPath("Shader/Base.vert.spv");
    mVertexShader->OnInit();

    mFragShader = make_shared<VulkanShaderWrapper>();
    mFragShader->SetShaderType(VK_SHADER_STAGE_FRAGMENT_BIT);
    mFragShader->SetShaderPath("Shader/Base.frag.spv");
    mFragShader->OnInit();
}

void VulkanGraphicsPipelineSystem::CreateDescriptorPool()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;
    auto pipelineComponent = VkRCenter::instance()->GetComponentFromActivePipeline<PipelineComponent>();
    if (!pipelineComponent)
        return;

    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);

    vkCreateDescriptorPool(deviceComponent->logicDevice, &poolInfo, nullptr, &pipelineComponent->mDescriptorPool);
}

void VulkanGraphicsPipelineSystem::CreateDescriptorSets()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;
    auto pipelineComponent = VkRCenter::instance()->GetComponentFromActivePipeline<PipelineComponent>();
    if (!pipelineComponent)
        return;

    std::vector<VkDescriptorSetLayout> layouts(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT, pipelineComponent->mDescriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pipelineComponent->mDescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    pipelineComponent->mDescriptorSets.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(deviceComponent->logicDevice, &allocInfo, pipelineComponent->mDescriptorSets.data()) != VK_SUCCESS)
        return;

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; i++)
    {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = mShaderBuffer->GetUniformBuffer()[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = pipelineComponent->mDescriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(deviceComponent->logicDevice, 1, &descriptorWrite, 0, nullptr);
    }
}

void VulkanGraphicsPipelineSystem::CreateDescriptorSetLayout()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;
    auto pipelineComponent = VkRCenter::instance()->GetComponentFromActivePipeline<PipelineComponent>();
    if (!pipelineComponent)
        return;

    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    vkCreateDescriptorSetLayout(deviceComponent->logicDevice, &layoutInfo, nullptr, &pipelineComponent->mDescriptorSetLayout);
}

void VulkanGraphicsPipelineSystem::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{
    auto renderPassComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanRenderPassComponent>();
    if (!renderPassComponent)
        return;
    auto pipelineComponent = VkRCenter::instance()->GetComponentFromActivePipeline<PipelineComponent>();
    if (!pipelineComponent)
        return;

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;  // Optional
    beginInfo.pInheritanceInfo = nullptr;  // Optional
    auto vkResult = vkBeginCommandBuffer(commandBuffer, &beginInfo);
    if (vkResult != VkResult::VK_SUCCESS)
        return;

    auto swapChainWrapper = VulkanManager::instance()->GetSwapChainWrapper();
    auto swapChainExtent = swapChainWrapper->GetSwapChainExtent();

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPassComponent->renderPass;
    renderPassInfo.framebuffer = swapChainWrapper->GetBuffer(imageIndex);
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineComponent->mPipeline);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapChainExtent.width;
    viewport.height = (float)swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    VkBuffer vertexBuffers[] = {mShaderBuffer->GetVertexBufferHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffer, mShaderBuffer->GetIndexBufferHandle(), 0, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineComponent->mPipelineLayout,
                            0,
                            1,
                            &pipelineComponent->mDescriptorSets[mCurrentFrame],
                            0,
                            nullptr);

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(mShaderBuffer->GetIndexSize()), 1, 0, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    vkEndCommandBuffer(commandBuffer);
}

void VulkanGraphicsPipelineSystem::UpdateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    auto swapChainWrapper = VulkanManager::instance()->GetSwapChainWrapper();
    auto swapChainExtent = swapChainWrapper->GetSwapChainExtent();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    memcpy(mShaderBuffer->GetUniformBufferMapped()[currentImage], &ubo, sizeof(ubo));
}
