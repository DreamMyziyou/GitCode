//
// Created by chenwei on 2024/1/9.
//

#ifndef WORKENGINE_IMODULE_H
#define WORKENGINE_IMODULE_H

#include "ModuleExport.h"

namespace Module
{

struct IModule
{
    virtual ~IModule() = default;
    virtual void StartupModule() {}
    virtual void ShutdownModule() {}
};

struct IManager
{
    virtual ~IManager() = default;
    virtual void RegisterModule(Module::IModule* module) = 0;
    virtual void UnregisterAll() = 0;
};

MODULE_API IManager* GetManager();

}  // namespace Module

#endif  // WORKENGINE_IMODULE_H
