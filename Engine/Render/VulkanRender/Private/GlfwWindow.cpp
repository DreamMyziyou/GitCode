//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Module/Logger/Logger.h"
#include "Render/RenderInterface/RenderComponent.h"
#include "VulkanDrawCall.h"
#include "VulkanManager.h"
#include "World/World.h"

GlfwWindow::GlfwWindow() {}

GlfwWindow::~GlfwWindow()
{
    DestroyResource();
}

void GlfwWindow::Run()
{
    if (!mWindow)
        return;

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        CheckUpdate();
        DrawCall();
    }

    vkDeviceWaitIdle(VulkanManager::instance()->GetVulkanDevice());
}

void GlfwWindow::CreateResource()
{
    if (mWindow != nullptr)
        return;

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);
}

void GlfwWindow::DestroyResource()
{
    if (nullptr == mWindow)
        return;

    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    Logger::Log(Logger::Level::Info, "VulkanRender", "Destroy GlfwWindow.");
}

void GlfwWindow::SetWH(int32 width, int32 height)
{
    mWidth = width;
    mHeight = height;
}

void GlfwWindow::SetWindowName(const String& name)
{
    mWindowName = name;
}

void GlfwWindow::CheckUpdate()
{
    auto world = World::GetWorld();
    auto positionView = world->view<Render::MeshComponent, Render::MaterialComponent>();
    for (const auto& [entityKey, mesh, material] : positionView.each())
    {}
}

void GlfwWindow::DrawCall()
{
    VulkanDrawCall drawCall;
    drawCall.Draw();
}
