//
// Created by WeslyChen on 2024/1/20.
//

#include "GlfwWindow.h"

#include "Core/Geometry/MeshComponent.h"
#include "Module/Logger/Logger.h"
#include "VulkanManager.h"
#include "World/World.h"

using namespace std;

void GlfwWindow::OnFramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    if (!app || !app->mDrawHandler)
        return;
    app->mDrawHandler->OnWindowResize();
}

GlfwWindow::GlfwWindow() {}

GlfwWindow::~GlfwWindow()
{
    DestroyResource();
}

void GlfwWindow::Run()
{
    if (!mWindow)
        return;

    mDrawHandler = make_unique<VulkanDrawHandler>();
    CheckUpdate();

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        DrawFrame();
    }

    vkDeviceWaitIdle(VulkanManager::instance()->GetDeviceWrapper()->GetLogicDevice());

    mDrawHandler = nullptr;
}

void GlfwWindow::CreateResource()
{
    if (mWindow != nullptr)
        return;

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetFramebufferSizeCallback(mWindow, OnFramebufferResizeCallback);
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
    if (!mDrawHandler)
        return;

    auto world = World::GetWorld();

    auto positionView = world->view<MeshComponent>();
    for (const auto& [entityKey, mesh] : positionView.each())
    {
        // test
        mDrawHandler->OnMeshUpdate(mesh);
        break;
    }
}

void GlfwWindow::DrawFrame()
{
    if (!mDrawHandler)
        return;

    mDrawHandler->DrawCall();
}
