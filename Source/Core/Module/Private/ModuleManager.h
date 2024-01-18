//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORKENGINE_MODULEMANAGER_H
#define WORKENGINE_MODULEMANAGER_H

#include <stack>

#include "Common/ClassMacro.h"
#include "IModule.h"

class ModuleManager final : public Module::IManager
{
    SINGLETON_CLASS(ModuleManager)

public:
    void RegisterModule(std::shared_ptr<Module::IModule> module) override;
    void ShutDownAllModule() override;

private:
    std::stack<std::shared_ptr<Module::IModule>> mModules;
};

#endif  // WORKENGINE_MODULEMANAGER_H
