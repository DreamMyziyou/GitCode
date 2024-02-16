//
// Created by WeslyChen on 2024/2/15.
//
#ifndef WORLDENGINE_UNIFORMBUFFER_H
#define WORLDENGINE_UNIFORMBUFFER_H

#include <glm/glm.hpp>

struct UniformBufferObject
{
    alignas(16) glm::mat4 model{1.0f};
    alignas(16) glm::mat4 view{1.0f};
    alignas(16) glm::mat4 proj{1.0f};
};

#endif  // WORLDENGINE_UNIFORMBUFFER_H
