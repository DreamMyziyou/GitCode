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
    VkSurfaceFormatKHR GetExpectSurfaceFormat() const { return mExpectSurfaceFormat; }
    VkPresentModeKHR GetExpectPresentMode() const { return mExpectPresentMode; }
    VkExtent2D GetExpectSwapChainExtent() const { return mExpectSwapChainExtent; }
    uint32 GetExpectSwapChainBufferCount() const { return mExpectSwapChainBufferCount; }
    const VkSurfaceCapabilitiesKHR& GetSurfaceCapabilities() const { return mSurfaceCapabilities; }

public:
    struct QueueFamilyIndices
    {
        std::optional<uint32> graphicsFamily{};
        std::optional<uint32> presentFamily{};

        bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };
    VulkanSurfaceWrapper::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    VulkanSurfaceWrapper::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D ChooseSwapExtent(VkPhysicalDevice device, const VkSurfaceCapabilitiesKHR& capabilities) const;

public:
    void OnUpdate(VkPhysicalDevice device);

private:
    VkSurfaceKHR mSurface = nullptr;
    VkSurfaceCapabilitiesKHR mSurfaceCapabilities;
    VkSurfaceFormatKHR mExpectSurfaceFormat;
    VkPresentModeKHR mExpectPresentMode;
    VkExtent2D mExpectSwapChainExtent;
    uint32 mExpectSwapChainBufferCount = 1;
};

#endif  // WORKENGINE_VULKANSURFACEWRAPPER_H
