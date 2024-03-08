//
// Created by WeslyChen on 2024/3/7.
//
#ifndef WORLDENGINE_VULKANCOMPONENT_H
#define WORLDENGINE_VULKANCOMPONENT_H

#include "VkRCenter.h"

struct VulkanInstanceComponent
{
    VkInstance instance = nullptr;

    bool applyValidationLayer = false;
    VkDebugUtilsMessengerEXT debugMessenger = nullptr;
};

#endif  // WORLDENGINE_VULKANCOMPONENT_H
