//
// Created by WeslyChen on 2024/2/3.
//
#ifndef WORLDENGINE_MESHCOMPONENT_H
#define WORLDENGINE_MESHCOMPONENT_H

#include <vector>

#include "GeometryExport.h"
#include "Vertex.h"

struct MeshComponent
{
    int dirtyVersion = 0;
    std::vector<Vertex> vertices;
};

#endif  // WORLDENGINE_MESHCOMPONENT_H
