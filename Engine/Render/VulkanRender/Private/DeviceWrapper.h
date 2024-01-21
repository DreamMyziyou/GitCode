//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_DEVICEWRAPPER_H
#define WORKENGINE_DEVICEWRAPPER_H

#include "VulkanHelper.h"

class DeviceWrapper final
{
public:
    DeviceWrapper() = default;
    ~DeviceWrapper() = default;
    DeviceWrapper(const DeviceWrapper&) = delete;
    DeviceWrapper& operator=(const DeviceWrapper&) = delete;

public:
    VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }

    void InitDevice(VkInstance instance);
    void UninitDevice();

private:
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();

private:
    VkInstance mInstance = nullptr;
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;
};

#endif  // WORKENGINE_DEVICEWRAPPER_H
