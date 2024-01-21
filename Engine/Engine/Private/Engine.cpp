//
// Created by WeslyChen on 2024/1/21.
//

#include "Engine.h"
#include "EngineManager.h"

Engine::IEngine* Engine::GetEngine()
{
    return EngineManager::instance();
}
