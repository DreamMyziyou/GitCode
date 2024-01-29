//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanSyncWrapper.h"

#include "VulkanManager.h"

void VulkanSyncWrapper::CreateResource()
{
    mImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    mRenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    mInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    auto device = VulkanManager::instance()->GetDevice();

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        auto vkResult = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mImageAvailableSemaphores[i]);
        if (vkResult != VK_SUCCESS)
            return;

        vkResult = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mRenderFinishedSemaphores[i]);
        if (vkResult != VK_SUCCESS)
            return;

        vkResult = vkCreateFence(device, &fenceInfo, nullptr, &mInFlightFences[i]);
        if (vkResult != VK_SUCCESS)
            return;
    }
}

void VulkanSyncWrapper::DestroyResource()
{
    auto device = VulkanManager::instance()->GetDevice();

    for (auto& item : mImageAvailableSemaphores)
        vkDestroySemaphore(device, item, nullptr);
    mImageAvailableSemaphores.clear();

    for (auto& item : mRenderFinishedSemaphores)
        vkDestroySemaphore(device, item, nullptr);
    mRenderFinishedSemaphores.clear();

    for (auto& item : mInFlightFences)
        vkDestroyFence(device, item, nullptr);
    mInFlightFences.clear();
}
