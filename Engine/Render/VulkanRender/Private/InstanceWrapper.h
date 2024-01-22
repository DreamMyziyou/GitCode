//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_INSTANCEWRAPPER_H
#define WORKENGINE_INSTANCEWRAPPER_H

#include "VulkanHelper.h"

class InstanceWrapper final
{
public:
    InstanceWrapper() = default;
    ~InstanceWrapper() = default;
    InstanceWrapper(const InstanceWrapper&) = delete;
    InstanceWrapper& operator=(const InstanceWrapper&) = delete;

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
    VkDebugUtilsMessengerEXT mDebugMessenger = nullptr;
};

#endif  // WORKENGINE_INSTANCEWRAPPER_H
