//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleManager.h"

void Module::RegisterModule(std::shared_ptr<Module::IModule> module, std::vector<size_t> deps)
{
    ModuleManager::instance().RegisterModule(module, std::move(deps));
}