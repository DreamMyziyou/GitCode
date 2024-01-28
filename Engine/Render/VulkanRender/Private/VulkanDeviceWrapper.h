//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_VULKANDEVICEWRAPPER_H
#define WORKENGINE_VULKANDEVICEWRAPPER_H

#include "VulkanResource.h"

class VulkanDeviceWrapper final : public IVulkanResource
{
public:
    VulkanDeviceWrapper() = default;
    ~VulkanDeviceWrapper() override = default;
    VulkanDeviceWrapper(const VulkanDeviceWrapper&) = delete;
    VulkanDeviceWrapper& operator=(const VulkanDeviceWrapper&) = delete;

public:
    void CreateResource() override;
    void DestroyResource() override;

public:
    VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
    VkDevice GetLogicDevice() const { return mLogicDevice; }
    VkQueue GetGraphicsQueue() const { return mGraphicsQueue; }
    VkQueue GetPresentQueue() const { return mPresentQueue; }
    VkCommandPool GetCommandPool() const { return mCommandPool; }
    VkCommandBuffer GetCommandBuffer() const { return mCommandBuffer; }

    VkSurfaceFormatKHR GetExpectSurfaceFormat() const { return mExpectSurfaceFormat; }
    VkPresentModeKHR GetExpectPresentMode() const { return mExpectPresentMode; }
    VkExtent2D GetExpectSwapChainExtent() const { return mExpectSwapChainExtent; }
    uint32 GetExpectSwapChainBufferCount() const { return mExpectSwapChainBufferCount; }

    const VkSurfaceCapabilitiesKHR& GetSurfaceCapabilities() const { return mSurfaceCapabilities; }

private:
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    VulkanDeviceWrapper::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();
    void CreateCommand();

private:
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;
    VkQueue mPresentQueue = nullptr;
    VkCommandPool mCommandPool = nullptr;
    VkCommandBuffer mCommandBuffer = nullptr;

    VkSurfaceCapabilitiesKHR mSurfaceCapabilities;
    VkSurfaceFormatKHR mExpectSurfaceFormat;
    VkPresentModeKHR mExpectPresentMode;
    VkExtent2D mExpectSwapChainExtent;
    uint32 mExpectSwapChainBufferCount = 1;
};

#endif  // WORKENGINE_VULKANDEVICEWRAPPER_H
