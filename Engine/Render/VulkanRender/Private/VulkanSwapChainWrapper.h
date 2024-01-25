//
// Created by WeslyChen on 2024/1/25.
//

#ifndef WORKENGINE_VULKANSWAPCHAINWRAPPER_H
#define WORKENGINE_VULKANSWAPCHAINWRAPPER_H

#include "VulkanResource.h"

class VulkanSwapChainWrapper final
{
public:
    VulkanSwapChainWrapper() = default;
    ~VulkanSwapChainWrapper() = default;
    VulkanSwapChainWrapper(const VulkanSwapChainWrapper&) = delete;
    VulkanSwapChainWrapper& operator=(const VulkanSwapChainWrapper&) = delete;

public:
    VkSwapchainKHR GetSwapChain() const { return mSwapChain; }

    void Create();
    void Destroy();

private:
    void CreateSwapChain();
    void CreateImageViews();

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;

private:
    VkSwapchainKHR mSwapChain = nullptr;
    std::vector<VkImage> mSwapChainImages;
    VkFormat mSwapChainImageFormat{};
    VkExtent2D mSwapChainExtent{};
    std::vector<VkImageView> mSwapChainImageViews;
};

#endif  // WORKENGINE_VULKANSWAPCHAINWRAPPER_H
