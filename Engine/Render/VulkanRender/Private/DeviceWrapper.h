//
// Created by WeslyChen on 2024/1/21.
//

#ifndef WORKENGINE_DEVICEWRAPPER_H
#define WORKENGINE_DEVICEWRAPPER_H

#include <vector>

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
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;

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
    void CreateSwapChain();
    void CreateImageViews();

private:
    // input
    VkInstance mInstance = nullptr;
    VkSurfaceKHR mSurface = nullptr;

    // device
    VkPhysicalDevice mPhysicalDevice = nullptr;
    VkDevice mLogicDevice = nullptr;
    VkQueue mGraphicsQueue = nullptr;

    // swap chain
    VkSwapchainKHR mSwapChain = nullptr;
    std::vector<VkImage> mSwapChainImages;
    VkFormat mSwapChainImageFormat{};
    VkExtent2D mSwapChainExtent{};
    std::vector<VkImageView> mSwapChainImageViews;
};

#endif  // WORKENGINE_DEVICEWRAPPER_H
