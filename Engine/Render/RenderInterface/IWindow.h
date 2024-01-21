//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_IWINDOW_H
#define WORKENGINE_IWINDOW_H

#include "Engine/EngineCore.h"

namespace Render
{

    struct IWindow
    {
        virtual ~IWindow() {}
        virtual void SetWH(int32 width, int32 height) = 0;
        virtual void SetWindowName(const String& name) = 0;
        virtual void Create() = 0;
        virtual void Run() = 0;
    };

}  // namespace Render

#endif  // WORKENGINE_IWINDOW_H
