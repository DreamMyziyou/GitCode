//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANSHADERWRAPPER_H
#define WORKENGINE_VULKANSHADERWRAPPER_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanShaderWrapper : IVulkanSubSystem
{
public:
    static constexpr const char* DEFAULT_SHADER_MAIN_NAME = "main";

public:
    VulkanShaderWrapper() = default;
    ~VulkanShaderWrapper() override = default;
    VulkanShaderWrapper(const VulkanShaderWrapper&) = delete;
    VulkanShaderWrapper& operator=(const VulkanShaderWrapper&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    const VkPipelineShaderStageCreateInfo& GetShaderCreateInfo() const { return mShaderCreateInfo; }
    void SetShaderType(VkShaderStageFlagBits type) { mType = type; }
    void SetShaderPath(String path) { mShaderPath = std::move(path); }

protected:
    VkShaderStageFlagBits mType = VK_SHADER_STAGE_VERTEX_BIT;
    String mShaderPath{};
    VkShaderModule mShader = nullptr;
    VkPipelineShaderStageCreateInfo mShaderCreateInfo;
};

#endif  // WORKENGINE_VULKANSHADERWRAPPER_H
