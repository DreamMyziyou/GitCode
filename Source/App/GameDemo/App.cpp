//
// Created by WeslyChen on 2024/1/14.
//

#include "App.h"

#include "Module/ModuleSingleton.h"

using namespace std;

void App::Start()
{
}

void App::Run() {}

void App::Stop()
{
    Module::GetManager()->UnregisterAll();
}
