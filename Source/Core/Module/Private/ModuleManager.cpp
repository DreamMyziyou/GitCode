//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

#include <format>
#include <typeinfo>

#include "Logger/Logger.h"

void ModuleManager::RegisterModule(Module::IModule* module)
{
    if (!module)
        return;

    Logger::LogInfo("Module", std::format("Loading Module {}.", GetModuleName(module)));
    module->StartupModule();
    mModules.push(module);
}

void ModuleManager::UnregisterAll()
{
    while (!mModules.empty())
    {
        auto module = mModules.top();
        module->ShutdownModule();
        Logger::LogInfo("Module", std::format("Unloading Module {}.", GetModuleName(module)));
        mModules.pop();
    }
}

String ModuleManager::GetModuleName(Module::IModule* module)
{
    if (!module)
        return "";

    const String CLASS_PRE = "class ";
    String className = typeid(*module).name();
    className = className.substr(CLASS_PRE.size());
    return className;
}
