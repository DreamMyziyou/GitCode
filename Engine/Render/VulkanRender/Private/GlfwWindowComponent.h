//
// Created by WeslyChen on 2024/2/25.
//
#ifndef WORLDENGINE_GLFWWINDOWCOMPONENT_H
#define WORLDENGINE_GLFWWINDOWCOMPONENT_H

#include "VkRCenter.h"

struct GlfwWindowComponent
{
    int32 width = 800;
    int32 height = 600;
    String windowName = "GlfwWindow";
    GLFWwindow* window = nullptr;
};

struct WindowResizeComponent
{
    int32 width = 0;
    int32 height = 0;
};

#endif  // WORLDENGINE_GLFWWINDOWCOMPONENT_H
