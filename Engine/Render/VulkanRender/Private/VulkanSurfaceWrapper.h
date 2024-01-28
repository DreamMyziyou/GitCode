//
// Created by WeslyChen on 2024/1/28.
//
#ifndef WORKENGINE_VULKANSURFACEWRAPPER_H
#define WORKENGINE_VULKANSURFACEWRAPPER_H

#include "VulkanResource.h"

class VulkanSurfaceWrapper final : public IVulkanResource
{
public:
    VulkanSurfaceWrapper() = default;
    ~VulkanSurfaceWrapper() override = default;
    VulkanSurfaceWrapper(const VulkanSurfaceWrapper&) = delete;
    VulkanSurfaceWrapper& operator=(const VulkanSurfaceWrapper&) = delete;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    VkSurfaceKHR GetSurface() const { return mSurface; }

private:
    VkSurfaceKHR mSurface = nullptr;
};

#endif  // WORKENGINE_VULKANSURFACEWRAPPER_H
