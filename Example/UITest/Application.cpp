//
// Created by WeslyChen on 2024/1/20.
//

#include "Application.h"

#include "Core/Common/DeleteMacro.h"
#include "Render/RenderManager/RenderManager.h"

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
