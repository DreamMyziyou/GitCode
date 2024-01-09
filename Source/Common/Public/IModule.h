//
// Created by chenwei on 2024/1/9.
//

#ifndef GITWORKSPACE_IMODULE_H
#define GITWORKSPACE_IMODULE_H

struct IModule
{
    virtual ~IModule() = default;
    virtual void StartupModule() {}
    virtual void ShutdownModule() {}
};

#endif//GITWORKSPACE_IMODULE_H
