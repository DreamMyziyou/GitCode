//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_GLFWWINDOW_H
#define WORKENGINE_GLFWWINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "WindowInterface.h"

class GlfwWindow final : public WindowInterface::IWindow
{
public:
    GlfwWindow();
    ~GlfwWindow();
    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow& operator=(const GlfwWindow&) = delete;

public:
    void Run() override;

private:
    GLFWwindow* mWindow = nullptr;
};

#endif  // WORKENGINE_GLFWWINDOW_H
