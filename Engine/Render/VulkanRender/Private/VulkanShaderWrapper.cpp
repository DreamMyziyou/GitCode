//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanShaderWrapper.h"
#include "VulkanManager.h"

#include <fstream>

using namespace std;

void VulkanShaderWrapper::CreateResource()
{
    if (mShader)
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
    auto vkResult = vkCreateShaderModule(VulkanManager::instance()->GetVulkanDevice(), &createInfo, nullptr, &shaderModule);
    if (vkResult != VkResult::VK_SUCCESS)
        return;
    mShader = shaderModule;

    mShaderCreateInfo = {};
    mShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    mShaderCreateInfo.stage = mType;
    mShaderCreateInfo.module = mShader;
    mShaderCreateInfo.pName = DEFAULT_SHADER_MAIN_NAME;
}

void VulkanShaderWrapper::DestroyResource()
{
    if (nullptr == mShader)
        return;

    vkDestroyShaderModule(VulkanManager::instance()->GetVulkanDevice(), mShader, nullptr);
    mShader = nullptr;
}
