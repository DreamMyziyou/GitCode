//
// Created by WeslyChen on 2024/2/25.
//
#include "GlfwWindowSystem.h"

#include "GlfwWindowComponent.h"
#include "VulkanManager.h"

using namespace std;

GlfwWindowComponent* GlfwWindowSystem::QueryGlfwWindowComponent()
{
    auto& windowEntity = VulkanResourceCenter::instance()->windowEntity;
    if (windowEntity == entt::null)
        return nullptr;

    auto& world = VulkanResourceCenter::instance()->world;
    return world.try_get<GlfwWindowComponent>(windowEntity);
}

GLFWwindow* GlfwWindowSystem::QueryGlfwWindowHandle()
{
    auto windowComponent = QueryGlfwWindowComponent();
    if (nullptr == windowComponent)
        return nullptr;

    return windowComponent->window;
}

void GlfwWindowSystem::OnInit()
{
    if (VulkanResourceCenter::instance()->windowEntity != entt::null)
        return;

    auto& world = VulkanResourceCenter::instance()->world;
    auto& windowEntity = VulkanResourceCenter::instance()->windowEntity;

    windowEntity = world.create();
    auto& windowComponent = world.emplace<GlfwWindowComponent>(windowEntity);

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    windowComponent.window = glfwCreateWindow(windowComponent.width, windowComponent.height, windowComponent.windowName.c_str(), nullptr, nullptr);

    glfwSetFramebufferSizeCallback(windowComponent.window, OnFramebufferResize);
}

void GlfwWindowSystem::OnDestroy()
{
    if (VulkanResourceCenter::instance()->windowEntity == entt::null)
        return;

    auto& world = VulkanResourceCenter::instance()->world;
    auto& windowEntity = VulkanResourceCenter::instance()->windowEntity;
    auto windowComponent = world.try_get<GlfwWindowComponent>(windowEntity);
    if (nullptr == windowComponent)
        return;

    glfwDestroyWindow(windowComponent->window);
    glfwTerminate();

    world.destroy(windowEntity);
    windowEntity = entt::null;
}

void GlfwWindowSystem::OnUpdate() {}

void GlfwWindowSystem::Run()
{
    auto pWindowComponent = GlfwWindowSystem::QueryGlfwWindowComponent();

    if (!pWindowComponent || !pWindowComponent->window)
        return;

    CheckUpdate();

    while (!glfwWindowShouldClose(pWindowComponent->window))
    {
        glfwPollEvents();
        DrawFrame();
    }

    vkDeviceWaitIdle(VulkanManager::instance()->GetDeviceWrapper()->GetLogicDevice());
}

void GlfwWindowSystem::OnFramebufferResize(GLFWwindow* window, int width, int height)
{
    auto& world = VulkanResourceCenter::instance()->world;
    auto view = world.view<GlfwWindowComponent>();
    if (view.empty())
        return;

    auto windowEntity = *view.begin();
    if (auto resizeComponent = world.try_get<WindowResizeComponent>(windowEntity); resizeComponent)
    {
        resizeComponent->width = width;
        resizeComponent->height = height;
    }
    else
    {
        auto& newResizeComponent = world.emplace<WindowResizeComponent>(windowEntity);
        newResizeComponent.width = width;
        newResizeComponent.height = height;
    }
}

void GlfwWindowSystem::CheckUpdate()
{
    auto pipeline = VulkanManager::instance()->GetPipelineWrapper();
    if (!pipeline)
        return;

    auto world = World::GetWorld();
    auto positionView = world->view<MeshComponent>();
    for (const auto& [entityKey, mesh] : positionView.each())
    {
        // test
        pipeline->OnMeshUpdate(mesh);
        break;
    }
}

void GlfwWindowSystem::DrawFrame()
{
    auto pipeline = VulkanManager::instance()->GetPipelineWrapper();
    if (!pipeline)
        return;

    pipeline->DrawCall();
}