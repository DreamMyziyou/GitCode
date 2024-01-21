//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANMANAGERIMPL_H
#define WORKENGINE_VULKANMANAGERIMPL_H

#include "GlfwWindow.h"

class VulkanManagerImpl
{
    friend class VulkanManager;

    void InitGlfw();
    void UninitGlfw();
    void InitVulkan();
    void UninitVulkan();

    void CheckVulkanExtension() const;

    VkResult mInitResult = VkResult::VK_SUCCESS;
    VkInstance mInstance = nullptr;
};

#endif  // WORKENGINE_VULKANMANAGERIMPL_H
