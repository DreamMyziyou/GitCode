//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANINSTANCEWRAPPER_H
#define WORKENGINE_VULKANINSTANCEWRAPPER_H

#include "VulkanHelper.h"

class VulkanInstanceWrapper final
{
public:
    VulkanInstanceWrapper() = default;
    ~VulkanInstanceWrapper() = default;
    VulkanInstanceWrapper(const VulkanInstanceWrapper&) = delete;
    VulkanInstanceWrapper& operator=(const VulkanInstanceWrapper&) = delete;

public:
    // get
    VkInstance GetVulkanInstance() const { return mInstance; }

    void InitVulkanInstance();
    void UninitVulkanInstance();

private:

    // check
    void CheckInstanceExtension() const;
    bool CheckValidationLayer() const;

    // build
    void BuildDebugInfoTo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
    void BuildDebugMessenger();

private:
    VkResult mInitResult = VkResult::VK_SUCCESS;
    VkInstance mInstance = nullptr;

    bool mApplyVaildationLayer = false;
    VkDebugUtilsMessengerEXT mDebugMessenger;
};

#endif  // WORKENGINE_VULKANINSTANCEWRAPPER_H
