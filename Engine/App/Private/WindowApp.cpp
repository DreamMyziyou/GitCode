//
// Created by WeslyChen on 2024/1/29.
//
#include "WindowApp.h"

#include "Render/RenderInterface/RenderComponent.h"
#include "Render/RenderManager/RenderManager.h"

struct WindowApp::Impl
{
    Render::IMainWindow* mainWindow = nullptr;
};

WindowApp::WindowApp()
{
    mImpl = new Impl();
}

WindowApp::~WindowApp()
{
    SAFE_DELETE(mImpl);
}

void WindowApp::Run()
{
    mImpl->mainWindow = RenderManager::CreateMainWindow(800, 600, "ApplicationWindow");
    mImpl->mainWindow->Run();
}
