//
// Created by WeslyChen on 2024/1/21.
//

#include "RenderManager.h"

#include "RenderMgr.h"

RenderManager::IManager* RenderManager::GetManager()
{
    return RenderMgr::instance();
}
