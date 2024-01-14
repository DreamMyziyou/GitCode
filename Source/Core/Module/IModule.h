//
// Created by chenwei on 2024/1/9.
//

#ifndef WORKENGINE_IMODULE_H
#define WORKENGINE_IMODULE_H

#include <memory>
#include <vector>

#include "BasicType/String.h"
#include "ModuleExport.h"

namespace Module
{

struct IModule
{
    virtual ~IModule() = default;
    constexpr String GetClassName() const { return typeid(*this).name(); }
    virtual void StartupModule() {}
    virtual void ShutdownModule() {}
};

MODULE_API void RegisterModule(std::shared_ptr<IModule> module, std::vector<String> deps);

}  // namespace Module

#endif  // WORKENGINE_IMODULE_H
