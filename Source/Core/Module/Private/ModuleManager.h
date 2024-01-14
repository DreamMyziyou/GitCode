//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORKENGINE_MODULEMANAGER_H
#define WORKENGINE_MODULEMANAGER_H

#include <map>

#include "Common/ClassDefine.h"
#include "IModule.h"

class ModuleManager final
{
    SINGLETON_CLASS(ModuleManager)

public:
    void RegisterModule(std::shared_ptr<Module::IModule> module, std::vector<String> deps);

private:
    struct ModuleInfo
    {
        std::shared_ptr<Module::IModule> module;
        std::vector<String> deps;
    };
    std::map<String, ModuleInfo> mModules;
};

#endif  // WORKENGINE_MODULEMANAGER_H
