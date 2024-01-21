//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManagerImpl.h"

#include <vector>

using namespace std;

void VulkanManagerImpl::InitGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void VulkanManagerImpl::UninitGlfw()
{
    glfwTerminate();
}

void VulkanManagerImpl::InitVulkan()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "WorkEngineGame";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "WorkEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = nullptr;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    mInitResult = vkCreateInstance(&createInfo, nullptr, &mInstance);
    if (mInitResult != VK_SUCCESS)
        Logger::LogFatal("VulkanRender", "Init Vulkan failed");
    else
        Logger::LogInfo("VulkanRender", "Init Vulkan success.");

    CheckVulkanExtension();
}

void VulkanManagerImpl::UninitVulkan()
{
    if (mInstance)
    {
        vkDestroyInstance(mInstance, nullptr);
        mInstance = nullptr;
        Logger::LogInfo("VulkanRender", "Uninit Vulkan.");
    }
}

void VulkanManagerImpl::CheckVulkanExtension() const
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    String logMsg = "available extensions:\n";
    for (const auto& extension : extensions)
    {
        logMsg += '\t';
        logMsg += extension.extensionName;
        logMsg += '\n';
    }
    Logger::LogInfo("VulkanRender", logMsg);
}
