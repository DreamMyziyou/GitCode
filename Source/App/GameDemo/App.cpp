//
// Created by WeslyChen on 2024/1/14.
//

#include "App.h"

#include "Module/ModuleSingleton.h"

using namespace std;

class TestModule01 : public Module::IModule
{
    SINGLETON_MODULE(TestModule01)
};

void App::Start()
{
    TestModule01::instance();
}

void App::Run() {}

void App::Stop()
{
    Module::GetManager()->ShutDownAllModule();
}
