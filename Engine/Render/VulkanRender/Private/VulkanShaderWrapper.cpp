//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanShaderWrapper.h"

#include <fstream>

#include "VulkanComponent.h"

using namespace std;

void VulkanShaderWrapper::OnInit()
{
    if (mShader)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    vector<char> buffer;
    ifstream file(mShaderPath, ios::ate | ios::binary);
    if (!file.is_open())
        return;

    size_t fileSize = (size_t)file.tellg();
    buffer.resize(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = buffer.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());

    VkShaderModule shaderModule;
    auto vkResult = vkCreateShaderModule(deviceComponent->mLogicDevice, &createInfo, nullptr, &shaderModule);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    mShader = shaderModule;

    mShaderCreateInfo = {};
    mShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    mShaderCreateInfo.stage = mType;
    mShaderCreateInfo.module = mShader;
    mShaderCreateInfo.pName = DEFAULT_SHADER_MAIN_NAME;
}

void VulkanShaderWrapper::OnDestroy()
{
    if (nullptr == mShader)
        return;
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    vkDestroyShaderModule(deviceComponent->mLogicDevice, mShader, nullptr);
    mShader = nullptr;
}

void VulkanShaderWrapper::OnUpdate() {}
