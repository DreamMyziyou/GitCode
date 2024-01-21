//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

#include <format>

#include "Module/Logger/Logger.h"

void ModuleManager::RegisterModule(ModuleCore::IModule* module)
{
    if (!module)
        return;

    Logger::LogInfo("ModuleCore", std::format("Loading Module {}.", GetModuleName(module)));
    module->StartupModule();
    mModules.push(module);
}

void ModuleManager::UnregisterAll()
{
    while (!mModules.empty())
    {
        auto module = mModules.top();
        module->ShutdownModule();
        Logger::LogInfo("ModuleCore", std::format("Unloading Module {}.", GetModuleName(module)));
        mModules.pop();
    }
}

String ModuleManager::GetModuleName(ModuleCore::IModule* module)
{
    if (!module)
        return "";

    const String CLASS_PRE = "class ";
    String className = typeid(*module).name();
    className = className.substr(CLASS_PRE.size());
    return className;
}
