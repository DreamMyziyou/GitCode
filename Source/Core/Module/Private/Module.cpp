//
// Created by WeslyChen on 2024/1/14.
//

#include "Module.h"

#include "ModuleManager.h"

Module::IManager* Module::GetManager()
{
    return ModuleManager::instance();
}