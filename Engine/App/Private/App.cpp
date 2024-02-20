//
// Created by WeslyChen on 2024/1/21.
//

#include "App.h"

#include "Core/Logger/Logger.h"
#include "Core/ModuleCore/ModuleCore.h"

App::App()
{
    Logger::WakeUp();
}

App::~App()
{
    ModuleCore::GetManager()->UnregisterAll();
}