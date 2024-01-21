//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_WINDOWINTERFACE_H
#define WORKENGINE_WINDOWINTERFACE_H

#include <memory>

#include "WindowExport.h"

namespace WindowInterface
{
    struct IWindow
    {
        virtual ~IWindow() {}

        virtual void Run() = 0;
    };

    struct IManager
    {
        virtual ~IManager() {}

        virtual std::shared_ptr<IWindow> CreateWindow() = 0;
    };

    WINDOW_API IManager* GetManager();

};  // namespace WindowInterface

#endif  // WORKENGINE_WINDOWINTERFACE_H
