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

class GlfwWindow final : public Render::IMainWindow, public IVulkanResource
{
private:
    static void OnFramebufferResizeCallback(GLFWwindow* window, int width, int height);

public:
    GlfwWindow();
    ~GlfwWindow() override;
    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow& operator=(const GlfwWindow&) = delete;

public:
    void Run() override;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    GLFWwindow* GetWindow() const { return mWindow; }

    void SetWH(int32 width, int32 height);
    void SetWindowName(const String& name);

private:
    // temp for check world
    void CheckUpdate();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void DrawFrame();

private:
    int32 mWidth = 800;
    int32 mHeight = 600;
    String mWindowName = "Window";
    GLFWwindow* mWindow = nullptr;

    bool mIsResize = false;
    int mCurrentFrame = 0;
};

#endif  // WORKENGINE_GLFWWINDOW_H
