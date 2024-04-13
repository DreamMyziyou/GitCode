//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANDEVICEWRAPPER_H
#define WORLDENGINE_VULKANDEVICEWRAPPER_H

#include "VkRCenter.h"
#include "VulkanSyncWrapper.h"

class VulkanDeviceWrapper final : public IVulkanSubSystem
{
public:
    VulkanDeviceWrapper() = default;
    ~VulkanDeviceWrapper() override = default;
    VulkanDeviceWrapper(const VulkanDeviceWrapper&) = delete;
    VulkanDeviceWrapper& operator=(const VulkanDeviceWrapper&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
    VkDevice GetLogicDevice() const { return mLogicDevice; }
    VkQueue GetGraphicsQueue() const { return mGraphicsQueue; }
    VkQueue GetPresentQueue() const { return mPresentQueue; }
    VkCommandPool GetCommandPool() const { return mCommandPool; }
    VkCommandBuffer GetCommandBuffer(size_t index) const { return mCommandBuffers[index]; }

    std::shared_ptr<VulkanSyncWrapper> GetSyncWrapper() const { return mSyncObject; }

    uint32 FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();
    void CreateCommand();

private:
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;
    VkQueue mPresentQueue = nullptr;
    VkCommandPool mCommandPool = nullptr;
    std::vector<VkCommandBuffer> mCommandBuffers;

    std::shared_ptr<VulkanSyncWrapper> mSyncObject = nullptr;
};

#endif  // WORLDENGINE_VULKANDEVICEWRAPPER_H
