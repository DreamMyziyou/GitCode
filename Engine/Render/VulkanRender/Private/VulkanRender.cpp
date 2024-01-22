//
// Created by WeslyChen on 2024/1/21.
//

#include "VulkanRender.h"

#include "VulkanManager.h"

VulkanRender::IManager* VulkanRender::GetManager()
{
    return VulkanManager::instance();
}

Render::IMainWindow* VulkanRender::GetMainWindow()
{
    return VulkanManager::instance()->GetMainWindow();
}
