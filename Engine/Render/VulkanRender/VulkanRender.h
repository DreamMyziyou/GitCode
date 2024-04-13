//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORLDENGINE_VULKANRENDER_H
#define WORLDENGINE_VULKANRENDER_H

#include "Render/RenderInterface/IWindow.h"
#include "VulkanRenderExport.h"

namespace VulkanRender
{
    struct IManager
    {
        virtual ~IManager() = default;
    };

    VULKANRENDER_API IManager* GetManager();
    VULKANRENDER_API Render::IMainWindow* CreateMainWindow(int width, int height, String title);

}  // namespace VulkanRender

#endif  // WORLDENGINE_VULKANRENDER_H
