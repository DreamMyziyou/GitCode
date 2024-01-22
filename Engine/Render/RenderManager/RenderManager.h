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
    };

    RENDERMANAGER_API IManager* GetManager();
    RENDERMANAGER_API Render::IMainWindow* GetMainWindow();

};  // namespace RenderManager

#endif  // WORKENGINE_RENDERMANAGER_H
