//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_GLFWWINDOW_H
#define WORKENGINE_GLFWWINDOW_H

#include "Core/Common/ClassMacro.h"
#include "DeviceWrapper.h"
#include "InstanceWrapper.h"
#include "Render/RenderInterface/IWindow.h"
#include "VulkanHelper.h"

class GlfwWindow final : public Render::IMainWindow
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
    void InitWindow();
    void InitSurface();
    void Destroy();

private:
    int32 mWidth = 800;
    int32 mHeight = 600;
    String mWindowName = "Window";
    GLFWwindow* mWindow = nullptr;
    InstanceWrapper mInstance;
    DeviceWrapper mDevice;
    VkSurfaceKHR mSurface = nullptr;
};

#endif  // WORKENGINE_GLFWWINDOW_H
