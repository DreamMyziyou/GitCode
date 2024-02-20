//
// Created by WeslyChen on 2024/1/14.
//

#include "ModuleCore.h"

#include "ModuleManager.h"

ModuleCore::IManager* ModuleCore::GetManager()
{
    return ModuleManager::instance();
}