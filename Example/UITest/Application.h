//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_APPLICATION_H
#define WORKENGINE_APPLICATION_H

#include "App/App.h"
#include "Core/Common/ClassMacro.h"

class Application final : public App
{
    SINGLETON_CLASS_CUSTOM_CONSTRUCT(Application)

public:
    void Start();
    void Run();
    void Stop();

private:
    struct Impl;
    Impl* mImpl = nullptr;
};

#endif  // WORKENGINE_APPLICATION_H
