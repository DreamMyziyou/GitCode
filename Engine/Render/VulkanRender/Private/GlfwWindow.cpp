//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Core/Geometry/MeshComponent.h"
#include "Core/World/World.h"
#include "GlfwWindowSystem.h"
#include "VulkanManager.h"

using namespace std;

GlfwWindow::GlfwWindow()
{
    GlfwWindowSystem::InitResource();
}

GlfwWindow::~GlfwWindow()
{
    GlfwWindowSystem::ReleaseResource();
}

void GlfwWindow::Run()
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

void GlfwWindow::CheckUpdate()
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

void GlfwWindow::DrawFrame()
{
    auto pipeline = VulkanManager::instance()->GetPipelineWrapper();
    if (!pipeline)
        return;

    pipeline->DrawCall();
}
