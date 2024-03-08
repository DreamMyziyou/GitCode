//
// Created by WeslyChen on 2024/2/3.
//
#ifndef WORLDENGINE_GEOMETRYTOVULKAN_H
#define WORLDENGINE_GEOMETRYTOVULKAN_H

#include <array>

#include "Core/Geometry/Vertex.h"
#include "VkRCenter.h"

namespace GeometryToVulkan
{
    VkVertexInputBindingDescription GetVertexBindingDescription();

    std::array<VkVertexInputAttributeDescription, 2> GetVertexAttributeDescriptions();

};  // namespace GeometryToVulkan

#endif  // WORLDENGINE_GEOMETRYTOVULKAN_H
