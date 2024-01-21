//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

#include "Core/Common/DeleteMacro.h"
#include "Render/RenderManager/RenderManager.h"

using namespace std;

struct Application::Impl
{
    shared_ptr<Render::IWindow> window = nullptr;
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

    mImpl->window = RenderManager::GetManager()->CreateWindow();
}

void Application::Run()
{
    if (!mImpl->window)
        return;

    mImpl->window->Run();
}

void Application::Stop()
{
    mImpl->window = nullptr;
}
