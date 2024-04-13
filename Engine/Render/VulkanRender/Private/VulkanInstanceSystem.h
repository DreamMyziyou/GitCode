//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANINSTANCESYSTEM_H
#define WORLDENGINE_VULKANINSTANCESYSTEM_H

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

#endif  // WORLDENGINE_VULKANINSTANCESYSTEM_H
