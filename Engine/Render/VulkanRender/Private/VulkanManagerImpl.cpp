//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanManagerImpl.h"

#include <vector>

using namespace std;

void VulkanManagerImpl::InitGlfwVulkan()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void VulkanManagerImpl::UninitGlfwVulkan()
{
    glfwTerminate();
}