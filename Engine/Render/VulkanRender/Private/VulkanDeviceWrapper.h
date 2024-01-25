//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANDEVICEWRAPPER_H
#define WORKENGINE_VULKANDEVICEWRAPPER_H

#include "VulkanResource.h"

class VulkanDeviceWrapper final
{
public:
    VulkanDeviceWrapper() = default;
    ~VulkanDeviceWrapper() = default;
    VulkanDeviceWrapper(const VulkanDeviceWrapper&) = delete;
    VulkanDeviceWrapper& operator=(const VulkanDeviceWrapper&) = delete;

public:
    VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
    VkDevice GetLogicDevice() const { return mLogicDevice; }
    VkQueue GetGraphicsQueue() const { return mGraphicsQueue; }

    void Create();
    void Destroy();

private:
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();

private:
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;
};

#endif  // WORKENGINE_VULKANDEVICEWRAPPER_H
