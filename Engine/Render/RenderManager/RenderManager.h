//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_RENDERMANAGER_H
#define WORLDENGINE_RENDERMANAGER_H

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
    RENDERMANAGER_API Render::IMainWindow* CreateMainWindow(int width, int height, String title);

}  // namespace RenderManager

#endif  // WORLDENGINE_RENDERMANAGER_H
