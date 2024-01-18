//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

void ModuleManager::RegisterModule(std::shared_ptr<Module::IModule> module)
{
    if (!module)
        return;

    module->StartupModule();
    mModules.push(module);
}

void ModuleManager::UnregisterAll()
{
    while (!mModules.empty())
    {
        mModules.top()->ShutdownModule();
        mModules.pop();
    }
}
