//
// Created by WeslyChen on 2024/2/25.
//
#include "GlfwWindowSystem.h"

#include "GlfwWindowComponent.h"
#include "VulkanManager.h"
#include "VulkanResourceCenter.h"

using namespace std;

GlfwWindowComponent* GlfwWindowSystem::QueryGlfwWindowComponent()
{
    auto& world = VulkanResourceCenter::instance()->world;
    auto view = world.view<GlfwWindowComponent>();
    if (view.empty())
        return nullptr;

    auto windowEntity = *view.begin();
    return world.try_get<GlfwWindowComponent>(windowEntity);
}

GLFWwindow* GlfwWindowSystem::QueryGlfwWindowHandle()
{
    auto windowComponent = QueryGlfwWindowComponent();
    if (nullptr == windowComponent)
        return nullptr;

    return windowComponent->window;
}

void GlfwWindowSystem::InitResource()
{
    auto& world = VulkanResourceCenter::instance()->world;
    auto view = world.view<GlfwWindowComponent>();
    if (!view.empty())
        return;

    auto windowEntity = world.create();
    auto& windowComponent = world.emplace<GlfwWindowComponent>(windowEntity);

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    windowComponent.window = glfwCreateWindow(windowComponent.width, windowComponent.height, windowComponent.windowName.c_str(), nullptr, nullptr);

    glfwSetFramebufferSizeCallback(windowComponent.window, OnFramebufferResize);
}

void GlfwWindowSystem::ReleaseResource()
{
    auto& world = VulkanResourceCenter::instance()->world;
    auto view = world.view<GlfwWindowComponent>();
    if (view.empty())
        return;

    auto windowEntity = *view.begin();
    auto windowComponent = world.try_get<GlfwWindowComponent>(windowEntity);
    if (nullptr == windowComponent)
        return;

    glfwDestroyWindow(windowComponent->window);
    world.destroy(windowEntity);

    glfwTerminate();
}

void GlfwWindowSystem::OnFramebufferResize(GLFWwindow* window, int width, int height)
{
    auto pipeline = VulkanManager::instance()->GetPipelineWrapper();
    if (!pipeline)
        return;

    VulkanManager::instance()->GetPipelineWrapper()->OnWindowResize();
}
