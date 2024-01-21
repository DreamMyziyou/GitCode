//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_RENDERMANAGER_H
#define WORKENGINE_RENDERMANAGER_H

#include <memory>

#include "Render/RenderInterface/IWindow.h"
#include "RenderManagerExport.h"

namespace RenderManager
{
    struct IManager
    {
        virtual ~IManager() {}

        virtual std::shared_ptr<Render::IWindow> CreateWindow() = 0;
    };

    RENDERMANAGER_API IManager* GetManager();

};  // namespace RenderManager

#endif  // WORKENGINE_RENDERMANAGER_H
