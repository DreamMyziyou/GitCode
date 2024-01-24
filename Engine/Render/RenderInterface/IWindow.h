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
        virtual ~IWindow() = default;

        virtual void Run() = 0;
    };

    struct IMainWindow : public IWindow
    {
    };

}  // namespace Render

#endif  // WORKENGINE_IWINDOW_H
