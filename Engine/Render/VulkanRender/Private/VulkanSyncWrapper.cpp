//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanSyncWrapper.h"

#include "VulkanManager.h"

void VulkanSyncWrapper::CreateResource()
{
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    auto device = VulkanManager::instance()->GetDevice();

    auto vkResult = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mImageAvailableSemaphore);
    if (vkResult != VK_SUCCESS)
        return;

    vkResult = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mRenderFinishedSemaphore);
    if (vkResult != VK_SUCCESS)
        return;

    vkResult = vkCreateFence(device, &fenceInfo, nullptr, &mInFlightFence);
}

void VulkanSyncWrapper::DestroyResource()
{
    auto device = VulkanManager::instance()->GetDevice();

    if (mImageAvailableSemaphore)
    {
        vkDestroySemaphore(device, mImageAvailableSemaphore, nullptr);
        mImageAvailableSemaphore = nullptr;
    }

    if (mRenderFinishedSemaphore)
    {
        vkDestroySemaphore(device, mRenderFinishedSemaphore, nullptr);
        mRenderFinishedSemaphore = nullptr;
    }

    if (mInFlightFence)
    {
        vkDestroyFence(device, mInFlightFence, nullptr);
        mInFlightFence = nullptr;
    }
}
