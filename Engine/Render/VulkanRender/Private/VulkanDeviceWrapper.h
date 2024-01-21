//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANDEVICEWRAPPER_H
#define WORKENGINE_VULKANDEVICEWRAPPER_H

#include "VulkanHelper.h"

class VulkanDeviceWrapper final
{
public:
    VulkanDeviceWrapper() = default;
    ~VulkanDeviceWrapper() = default;
    VulkanDeviceWrapper(const VulkanDeviceWrapper&) = delete;
    VulkanDeviceWrapper& operator=(const VulkanDeviceWrapper&) = delete;

public:
    VkPhysicalDevice GetDevice() const { return mDevice; }

    void InitDevice(VkInstance instance);

private:
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;

private:
    VkInstance mInstance = nullptr;
    VkPhysicalDevice mDevice = nullptr;
};

#endif  // WORKENGINE_VULKANDEVICEWRAPPER_H
