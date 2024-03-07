//
// Created by WeslyChen on 2024/2/25.
//
#ifndef WORLDENGINE_GLFWWINDOWSYSTEM_H
#define WORLDENGINE_GLFWWINDOWSYSTEM_H

#include "GlfwWindowComponent.h"
#include "Render/RenderInterface/IWindow.h"
#include "VulkanResource.h"

class GlfwWindowSystem final : public IVulkanSubSystem, public Render::IMainWindow
{
public:
    GlfwWindowSystem() = default;
    ~GlfwWindowSystem() override = default;
    GlfwWindowSystem(const GlfwWindowSystem&) = delete;
    GlfwWindowSystem& operator=(const GlfwWindowSystem&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    void Run() override;

public:
    static GlfwWindowComponent* QueryGlfwWindowComponent();
    static GLFWwindow* QueryGlfwWindowHandle();
    static void OnFramebufferResize(GLFWwindow* window, int width, int height);

private:
    // temp for check world
    void CheckUpdate();

    void DrawFrame();
};

#endif  // WORLDENGINE_GLFWWINDOWSYSTEM_H
