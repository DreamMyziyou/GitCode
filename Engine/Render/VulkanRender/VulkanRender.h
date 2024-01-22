//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANRENDER_H
#define WORKENGINE_VULKANRENDER_H

#include "VulkanRenderExport.h"
#include "Render/RenderInterface/IWindow.h"

namespace VulkanRender
{
    struct IManager
    {
        virtual ~IManager() {}
    };

    VULKANRENDER_API IManager* GetManager();
    VULKANRENDER_API Render::IMainWindow* GetMainWindow();

}  // namespace VulkanRender

#endif  // WORKENGINE_VULKANRENDER_H
