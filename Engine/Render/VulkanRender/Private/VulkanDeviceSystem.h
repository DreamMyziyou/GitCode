//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANDEVICESYSTEM_H
#define WORLDENGINE_VULKANDEVICESYSTEM_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanDeviceSystem final : public IVulkanSubSystem
{
public:
    VulkanDeviceSystem() = default;
    ~VulkanDeviceSystem() override = default;
    VulkanDeviceSystem(const VulkanDeviceSystem&) = delete;
    VulkanDeviceSystem& operator=(const VulkanDeviceSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

private:
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();
    void CreateCommand();
    void CreateSync();
};

#endif  // WORLDENGINE_VULKANDEVICESYSTEM_H
