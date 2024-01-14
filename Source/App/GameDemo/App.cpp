//
// Created by WeslyChen on 2024/1/14.
//

#include "App.h"

#include "Module/IModule.h"

using namespace std;

class TestModule : public Module::IModule
{
};

void App::Init()
{
    Module::RegisterModule(make_shared<TestModule>(), {});
}

void App::Run() {}
