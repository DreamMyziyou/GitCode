//
// Created by chenwei on 2024/1/9.
//

#ifndef WORKENGINE_IMODULE_H
#define WORKENGINE_IMODULE_H


struct IModule
{
    virtual ~IModule() = default;
    virtual void StartupModule() {}
    virtual void ShutdownModule() {}
};


#endif//WORKENGINE_IMODULE_H
