//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_GLFWWINDOW_H
#define WORKENGINE_GLFWWINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Render/RenderInterface/IWindow.h"

class GlfwWindow final : public Render::IWindow
{
public:
    GlfwWindow();
    ~GlfwWindow() override;
    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow& operator=(const GlfwWindow&) = delete;

public:
    void SetWH(int32 width, int32 height) override;
    void SetWindowName(const String& name) override;
    void Create() override;
    void Run() override;

private:
    int32 mWidth = 800;
    int32 mHeight = 600;
    String mWindowName = "Window";
    GLFWwindow* mWindow = nullptr;
};

#endif  // WORKENGINE_GLFWWINDOW_H
