//
// Created by WeslyChen on 2024/2/25.
//
#ifndef WORLDENGINE_GLFWWINDOWCOMPONENT_H
#define WORLDENGINE_GLFWWINDOWCOMPONENT_H

#include "VulkanResource.h"

struct GlfwWindowComponent
{
    int32 width = 800;
    int32 height = 600;
    String windowName = "GlfwWindow";
    GLFWwindow* window = nullptr;
};

#endif  // WORLDENGINE_GLFWWINDOWCOMPONENT_H
