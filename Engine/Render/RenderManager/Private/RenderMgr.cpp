//
// Created by WeslyChen on 2024/1/21.
//

#include "RenderMgr.h"

#include "Render/VulkanRender/VulkanManager.h"

std::shared_ptr<Render::IWindow> RenderMgr::CreateWindow()
{
    return VulkanManager::instance()->CreateGlfwWindow();
}
