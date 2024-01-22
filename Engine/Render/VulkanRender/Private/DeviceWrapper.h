//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_DEVICEWRAPPER_H
#define WORKENGINE_DEVICEWRAPPER_H

#include "VulkanHelper.h"

class DeviceWrapper final
{
public:
    DeviceWrapper() = default;
    ~DeviceWrapper() = default;
    DeviceWrapper(const DeviceWrapper&) = delete;
    DeviceWrapper& operator=(const DeviceWrapper&) = delete;

public:
    VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
    VkDevice GetLogicDevice() const { return mLogicDevice; }

    void InitDevice(VkInstance instance, VkSurfaceKHR surface);
    void UninitDevice();

private:
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    int32 ScoreDeviceSuitability(VkPhysicalDevice device) const;

    struct QueueFamilyIndices
    {
        std::optional<uint32> graphicsFamily{};
        std::optional<uint32> presentFamily{};

        bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;

    void CreatePhysicalDevice();
    void CreateLogicDevice();

private:
    // input
    VkInstance mInstance = nullptr;
    VkSurfaceKHR mSurface = nullptr;

    // create
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;
    VkSwapchainKHR mSwapChain = nullptr;
};

#endif  // WORKENGINE_DEVICEWRAPPER_H
