//
// Created by WeslyChen on 2024/2/25.
//
#ifndef WORLDENGINE_GLFWWINDOWSYSTEM_H
#define WORLDENGINE_GLFWWINDOWSYSTEM_H

#include "GlfwWindowComponent.h"
#include "VulkanResource.h"

class GlfwWindowSystem
{
public:
    static GlfwWindowComponent* QueryGlfwWindowComponent();
    static GLFWwindow* QueryGlfwWindowHandle();

    static void InitResource();
    static void ReleaseResource();

private:
    static void OnFramebufferResize(GLFWwindow* window, int width, int height);
};

#endif  // WORLDENGINE_GLFWWINDOWSYSTEM_H
