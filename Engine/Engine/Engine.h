//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_ENGINE_H
#define WORKENGINE_ENGINE_H

#include "EngineExport.h"

namespace Engine
{
    struct IEngine
    {
    };

    ENGINE_API IEngine* GetEngine();
}  // namespace Engine

#endif  // WORKENGINE_ENGINE_H
