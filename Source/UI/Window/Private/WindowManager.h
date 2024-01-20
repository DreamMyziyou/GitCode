//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WINDOWMANAGER_H
#define WORKENGINE_WINDOWMANAGER_H

#include "Module/ModuleSingleton.h"
#include "WindowInterface.h"

class WindowManager final : Module::IModule, public WindowInterface::IManager
{
    SINGLETON_MODULE(WindowManager)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    std::shared_ptr<WindowInterface::IWindow> CreateWindow() override;
};

#endif  // WORKENGINE_WINDOWMANAGER_H
