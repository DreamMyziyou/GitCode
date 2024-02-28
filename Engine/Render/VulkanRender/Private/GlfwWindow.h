//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_GLFWWINDOW_H
#define WORKENGINE_GLFWWINDOW_H

#include "Core/Common/ClassMacro.h"
#include "Render/RenderInterface/IWindow.h"
#include "VulkanDeviceWrapper.h"
#include "VulkanInstanceWrapper.h"
#include "VulkanResource.h"

class GlfwWindow final : public Render::IMainWindow
{
public:
    GlfwWindow();
    ~GlfwWindow() override;
    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow& operator=(const GlfwWindow&) = delete;

public:
    void Run() override;

private:
    // temp for check world
    void CheckUpdate();

    void DrawFrame();
};

#endif  // WORKENGINE_GLFWWINDOW_H
