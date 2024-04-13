//
// Created by WeslyChen on 2024/2/25.
//
#ifndef WORLDENGINE_GLFWWINDOWSYSTEM_H
#define WORLDENGINE_GLFWWINDOWSYSTEM_H

#include "GlfwWindowComponent.h"
#include "IVulkanSubSystem.h"
#include "Render/RenderInterface/IWindow.h"
#include "VkRCenter.h"

class GlfwWindowSystem final : public IVulkanSubSystem
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

private:
    static void OnFramebufferResize(GLFWwindow* window, int width, int height);
};

#endif  // WORLDENGINE_GLFWWINDOWSYSTEM_H
