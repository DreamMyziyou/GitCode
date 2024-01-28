//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

#include "Core/Common/DeleteMacro.h"
#include "Render/RenderInterface/RenderComponent.h"
#include "Render/RenderManager/RenderManager.h"
#include "World/World.h"

using namespace std;

struct Application::Impl
{
    Render::IMainWindow* mainWindow = nullptr;
};

Application::Application()
{
    mImpl = new Impl();
}

Application::~Application()
{
    SAFE_DELETE(mImpl);
}

void Application::Start()
{
    Stop();

    mImpl->mainWindow = RenderManager::CreateMainWindow(800, 600, "ApplicationWindow");

    auto world = World::GetWorld();
    if (!world)
        return;
    auto object = world->create();
    world->emplace<Render::MeshComponent>(object, Render::MeshComponent::Type::Default, "HelloTriangle");
    world->emplace<Render::MaterialComponent>(object, "Base");
}

void Application::Run()
{
    if (!mImpl->mainWindow)
        return;

    mImpl->mainWindow->Run();
}

void Application::Stop()
{
    mImpl->mainWindow = nullptr;
}
