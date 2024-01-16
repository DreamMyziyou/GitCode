//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

void ModuleManager::RegisterModule(std::shared_ptr<Module::IModule> module, std::vector<size_t> deps)
{
    if (!module)
        return;

    size_t key = typeid(*module).hash_code();
    ModuleInfo info;
    info.module = std::move(module);
    info.deps = std::move(deps);
    mModules[key] = std::move(info);
}
