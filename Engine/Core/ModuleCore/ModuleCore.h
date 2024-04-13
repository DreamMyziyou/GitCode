//
// Created by chenwei on 2024/1/9.
//

#ifndef WORLDENGINE_MODULECORE_H
#define WORLDENGINE_MODULECORE_H

#include "ModuleCoreExport.h"

namespace ModuleCore
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
        virtual void RegisterModule(ModuleCore::IModule* module) = 0;
        virtual void UnregisterAll() = 0;
    };

    MODULECORE_API IManager* GetManager();

}  // namespace ModuleCore

#endif  // WORLDENGINE_MODULECORE_H
