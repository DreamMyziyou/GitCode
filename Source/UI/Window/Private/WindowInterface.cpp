//
// Created by WeslyChen on 2024/1/20.
//

#include "WindowInterface.h"

#include "WindowManager.h"

WindowInterface::IManager* WindowInterface::GetManager()
{
    return WindowManager::instance();
}
