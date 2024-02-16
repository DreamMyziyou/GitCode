//
// Created by WeslyChen on 2024/2/3.
//
#ifndef WORLDENGINE_MESHCOMPONENT_H
#define WORLDENGINE_MESHCOMPONENT_H

#include <vector>

#include "Engine/EngineCore.h"
#include "Vertex.h"

struct MeshComponent
{
    int dirtyVersion = 0;
    std::vector<Vertex> vertices;
    std::vector<uint16> indices;
};

#endif  // WORLDENGINE_MESHCOMPONENT_H
