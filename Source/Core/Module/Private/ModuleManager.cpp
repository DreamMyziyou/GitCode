//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

void ModuleManager::RegisterModule(std::shared_ptr<Module::IModule> module, std::vector<String> deps)
{
    if (!module)
        return;

    auto key = module->GetClassName();
    ModuleInfo info;
    info.module = std::move(module);
    info.deps = std::move(deps);
    mModules[key] = std::move(info);
}
