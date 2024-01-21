//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGERIMPL_H
#define WORKENGINE_VULKANMANAGERIMPL_H

#include "VulkanInstanceWrapper.h"
#include "VulkanDeviceWrapper.h"

class VulkanManagerImpl
{
    friend class VulkanManager;

    // VulkanManager call
    void InitGlfw();
    void UninitGlfw();
    void InitVulkan();
    void UninitVulkan();

    VulkanInstanceWrapper mInstance;
    VulkanDeviceWrapper mDevice;
};

#endif  // WORKENGINE_VULKANMANAGERIMPL_H
