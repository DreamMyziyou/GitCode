//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Module/Logger/Logger.h"
#include "Render/RenderInterface/RenderComponent.h"
#include "VulkanManager.h"
#include "World/World.h"

void GlfwWindow::OnFramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    app->mIsResize = true;
}

GlfwWindow::GlfwWindow() {}

GlfwWindow::~GlfwWindow()
{
    DestroyResource();
}

void GlfwWindow::Run()
{
    if (!mWindow)
        return;

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        CheckUpdate();
        DrawFrame();
    }

    vkDeviceWaitIdle(VulkanManager::instance()->GetDeviceWrapper()->GetLogicDevice());
}

void GlfwWindow::CreateResource()
{
    if (mWindow != nullptr)
        return;

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetFramebufferSizeCallback(mWindow, OnFramebufferResizeCallback);
}

void GlfwWindow::DestroyResource()
{
    if (nullptr == mWindow)
        return;

    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    Logger::Log(Logger::Level::Info, "VulkanRender", "Destroy GlfwWindow.");
}

void GlfwWindow::SetWH(int32 width, int32 height)
{
    mWidth = width;
    mHeight = height;
}

void GlfwWindow::SetWindowName(const String& name)
{
    mWindowName = name;
}

void GlfwWindow::CheckUpdate()
{
    auto world = World::GetWorld();
    auto positionView = world->view<Render::MeshComponent, Render::MaterialComponent>();
    for (const auto& [entityKey, mesh, material] : positionView.each())
    {}
}

void GlfwWindow::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;  // Optional
    beginInfo.pInheritanceInfo = nullptr;  // Optional
    auto vkResult = vkBeginCommandBuffer(commandBuffer, &beginInfo);
    if (vkResult != VkResult::VK_SUCCESS)
        return;

    auto swapChainWrapper = VulkanManager::instance()->GetSwapChainWrapper();
    auto swapChainExtent = swapChainWrapper->GetSwapChainExtent();
    auto graphicsPipeline = VulkanManager::instance()->GetPipelineWrapper()->GetPipeline();

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = VulkanManager::instance()->GetRenderPass();
    renderPassInfo.framebuffer = swapChainWrapper->GetBuffer(imageIndex);
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

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

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    vkEndCommandBuffer(commandBuffer);
}

void GlfwWindow::DrawFrame()
{
    auto deviceWrapper = VulkanManager::instance()->GetDeviceWrapper();
    auto device = deviceWrapper->GetLogicDevice();
    auto syncObject = deviceWrapper->GetSyncWrapper();
    auto inFlightFence = syncObject->GetFence(mCurrentFrame);
    auto imageAvailableSemaphore = syncObject->GetImageAvailableSemaphore(mCurrentFrame);
    auto renderFinishedSemaphore = syncObject->GetFinishedSemaphore(mCurrentFrame);
    auto swapChain = VulkanManager::instance()->GetSwapChainWrapper()->GetSwapChain();
    auto commandBuffer = deviceWrapper->GetCommandBuffer(mCurrentFrame);
    auto graphicsQueue = deviceWrapper->GetGraphicsQueue();
    auto presentQueue = deviceWrapper->GetPresentQueue();

    vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        VulkanManager::instance()->ReCreateSwapChain();
        return;
    }

    vkResetFences(device, 1, &inFlightFence);

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
    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS)
        return;

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    result = vkQueuePresentKHR(presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || mIsResize)
    {
        mIsResize = false;
        VulkanManager::instance()->ReCreateSwapChain();
        return;
    }

    mCurrentFrame = (mCurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
