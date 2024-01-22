//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGERIMPL_H
#define WORKENGINE_VULKANMANAGERIMPL_H

#include "GlfwWindow.h"

class VulkanManagerImpl
{
    friend class VulkanManager;

    // VulkanManager call
    void InitGlfwVulkan();
    void UninitGlfwVulkan();

    GlfwWindow mMainWindow;
};

#endif  // WORKENGINE_VULKANMANAGERIMPL_H
