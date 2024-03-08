//
// Created by WeslyChen on 2024/1/25.
//

#ifndef WORKENGINE_VULKANSWAPCHAINWRAPPER_H
#define WORKENGINE_VULKANSWAPCHAINWRAPPER_H

#include "IVulkanSubSystem.h"
#include "VkRCenter.h"

class VulkanSwapChainWrapper final : public IVulkanSubSystem
{
public:
    VulkanSwapChainWrapper() = default;
    ~VulkanSwapChainWrapper() override = default;
    VulkanSwapChainWrapper(const VulkanSwapChainWrapper&) = delete;
    VulkanSwapChainWrapper& operator=(const VulkanSwapChainWrapper&) = delete;

public:
    void OnInit() override;
    void OnDestroy() override;
    void OnUpdate() override;

public:
    VkSwapchainKHR GetSwapChain() const { return mSwapChain; }
    VkExtent2D GetSwapChainExtent() const { return mSwapChainExtent; }
    VkFramebuffer GetBuffer(size_t bufferIndex) const;

private:
    void CreateSwapChain();
    void CreateImageViews();
    void CreateFrameBuffers();

private:
    VkSwapchainKHR mSwapChain = nullptr;
    std::vector<VkImage> mSwapChainImages;
    VkFormat mSwapChainImageFormat{};
    VkExtent2D mSwapChainExtent{};
    std::vector<VkImageView> mSwapChainImageViews;
    std::vector<VkFramebuffer> mSwapChainFrameBuffers;
};

#endif  // WORKENGINE_VULKANSWAPCHAINWRAPPER_H
