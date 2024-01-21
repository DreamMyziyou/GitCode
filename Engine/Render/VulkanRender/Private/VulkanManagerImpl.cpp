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
    mInstance.InitVulkanInstance();
    mDevice.InitDevice(mInstance.GetVulkanInstance());
}

void VulkanManagerImpl::UninitVulkan()
{
    mDevice.UninitDevice();
    mInstance.UninitVulkanInstance();
}