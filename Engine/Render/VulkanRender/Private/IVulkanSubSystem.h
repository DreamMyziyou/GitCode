//
// Created by WeslyChen on 2024/3/7.
//
#ifndef WORLDENGINE_IVULKANSUBSYSTEM_H
#define WORLDENGINE_IVULKANSUBSYSTEM_H

struct IVulkanSubSystem
{
    virtual ~IVulkanSubSystem() = default;

    virtual void OnInit() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnUpdate() = 0;
};

#endif  // WORLDENGINE_IVULKANSUBSYSTEM_H
