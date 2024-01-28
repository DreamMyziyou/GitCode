//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANSYNCWRAPPER_H
#define WORKENGINE_VULKANSYNCWRAPPER_H

#include "VulkanResource.h"

class VulkanSyncWrapper final : public IVulkanResource
{
public:
    VulkanSyncWrapper() = default;
    ~VulkanSyncWrapper() override = default;
    VulkanSyncWrapper(const VulkanSyncWrapper&) = delete;
    VulkanSyncWrapper& operator=(const VulkanSyncWrapper&) = delete;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    VkSemaphore GetImageAvailableSemaphore() const { return mImageAvailableSemaphore; }
    VkSemaphore GetFinishedSemaphore() const { return mRenderFinishedSemaphore; }
    VkFence GetFence() const { return mInFlightFence; }

private:
    VkSemaphore mImageAvailableSemaphore;
    VkSemaphore mRenderFinishedSemaphore;
    VkFence mInFlightFence;
};

#endif  // WORKENGINE_VULKANSYNCWRAPPER_H
