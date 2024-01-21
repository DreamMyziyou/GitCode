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
    void InitGlfw();
    void UninitGlfw();
    void InitVulkan();
    void UninitVulkan();

    // check
    void CheckInstanceExtension() const;
    bool CheckValidationLayer() const;

    // build
    void BuildDebugInfoTo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
    void BuildDebugMessenger();

    VkResult mInitResult = VkResult::VK_SUCCESS;
    VkInstance mInstance = nullptr;

    bool mApplyVaildationLayer = false;
    VkDebugUtilsMessengerEXT mDebugMessenger;
};

#endif  // WORKENGINE_VULKANMANAGERIMPL_H
