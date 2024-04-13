//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORLDENGINE_APPLICATION_H
#define WORLDENGINE_APPLICATION_H

#include "App/WindowApp.h"
#include "Engine.h"

class Application final : public WindowApp
{
    SINGLETON_CLASS_CUSTOM_CONSTRUCT(Application)
};

#endif  // WORLDENGINE_APPLICATION_H
