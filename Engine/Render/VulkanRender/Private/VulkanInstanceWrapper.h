//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANINSTANCEWRAPPER_H
#define WORKENGINE_VULKANINSTANCEWRAPPER_H

#include "VulkanResource.h"

class VulkanInstanceWrapper final : public IVulkanSubSystem
{
public:
    VulkanInstanceWrapper() = default;
    ~VulkanInstanceWrapper() override = default;
    VulkanInstanceWrapper(const VulkanInstanceWrapper&) = delete;
    VulkanInstanceWrapper& operator=(const VulkanInstanceWrapper&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    VkInstance GetVulkanInstance() const { return mInstance; }

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

    bool mApplyValidationLayer = false;
    VkDebugUtilsMessengerEXT mDebugMessenger = nullptr;
};

#endif  // WORKENGINE_VULKANINSTANCEWRAPPER_H
