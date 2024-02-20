//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_APPLICATION_H
#define WORKENGINE_APPLICATION_H

#include "App/WindowApp.h"
#include "Core/Engine/Engine.h"

class Application final : public WindowApp
{
    SINGLETON_CLASS_CUSTOM_CONSTRUCT(Application)
};

#endif  // WORKENGINE_APPLICATION_H
