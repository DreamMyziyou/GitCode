//
// Created by WeslyChen on 2024/1/27.
//
#ifndef WORKENGINE_RENDERCOMPONENT_H
#define WORKENGINE_RENDERCOMPONENT_H

#include "Engine/EngineCore.h"

namespace Render
{
    struct MeshComponent
    {
        enum class Type : uint8
        {
            Internal,
            Default = Internal,
        };

        Type type = Type::Default;
        String name;
    };

    struct MaterialComponent
    {
        String name;
    };

}  // namespace Render

#endif  // WORKENGINE_RENDERCOMPONENT_H
