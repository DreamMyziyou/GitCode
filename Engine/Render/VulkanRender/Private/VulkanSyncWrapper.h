//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORLDENGINE_VULKANSYNCWRAPPER_H
#define WORLDENGINE_VULKANSYNCWRAPPER_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanSyncWrapper final : public IVulkanSubSystem
{
public:
    VulkanSyncWrapper() = default;
    ~VulkanSyncWrapper() override = default;
    VulkanSyncWrapper(const VulkanSyncWrapper&) = delete;
    VulkanSyncWrapper& operator=(const VulkanSyncWrapper&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    VkSemaphore GetImageAvailableSemaphore(int index) const { return mImageAvailableSemaphores[index]; }
    VkSemaphore GetFinishedSemaphore(int index) const { return mRenderFinishedSemaphores[index]; }
    VkFence GetFence(int index) const { return mInFlightFences[index]; }

private:
    std::vector<VkSemaphore> mImageAvailableSemaphores;
    std::vector<VkSemaphore> mRenderFinishedSemaphores;
    std::vector<VkFence> mInFlightFences;
};

#endif  // WORLDENGINE_VULKANSYNCWRAPPER_H
