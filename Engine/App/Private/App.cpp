//
// Created by WeslyChen on 2024/1/21.
//

#include "App.h"
#include "Module/Logger/Logger.h"
#include "Module/ModuleCore/ModuleCore.h"

App::App()
{
    Logger::WakeUp();
}

App::~App()
{
    ModuleCore::GetManager()->UnregisterAll();
}