//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_IWINDOW_H
#define WORLDENGINE_IWINDOW_H

#include "Engine.h"

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

#endif  // WORLDENGINE_IWINDOW_H
