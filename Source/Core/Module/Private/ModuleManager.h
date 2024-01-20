//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORKENGINE_MODULEMANAGER_H
#define WORKENGINE_MODULEMANAGER_H

#include <stack>

#include "BasicType/String.h"
#include "Common/ClassMacro.h"
#include "Module.h"

class ModuleManager final : public Module::IManager
{
    SINGLETON_CLASS(ModuleManager)

public:
    void RegisterModule(Module::IModule* module) override;
    void UnregisterAll() override;

private:
    static String GetModuleName(Module::IModule* module);

private:
    std::stack<Module::IModule*> mModules;
};

#endif  // WORKENGINE_MODULEMANAGER_H
