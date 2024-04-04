//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANINSTANCESYSTEM_H
#define WORKENGINE_VULKANINSTANCESYSTEM_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanInstanceSystem final : public IVulkanSubSystem
{
public:
    VulkanInstanceSystem() = default;
    ~VulkanInstanceSystem() override = default;
    VulkanInstanceSystem(const VulkanInstanceSystem&) = delete;
    VulkanInstanceSystem& operator=(const VulkanInstanceSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

private:
    // check
    void CheckInstanceExtension() const;
    bool CheckValidationLayer() const;

    // build
    void BuildDebugInfoTo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
    void BuildDebugMessenger();
};

#endif  // WORKENGINE_VULKANINSTANCESYSTEM_H
