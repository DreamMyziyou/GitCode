//
// Created by WeslyChen on 2024/2/3.
//
#ifndef WORLDENGINE_MESHCOMPONENT_H
#define WORLDENGINE_MESHCOMPONENT_H

#include <vector>

#include "Engine.h"
#include "Vertex.h"

struct MeshComponent
{
    bool dirty = true;
    std::vector<Vertex> vertices;
    std::vector<uint16> indices;
};

#endif  // WORLDENGINE_MESHCOMPONENT_H
