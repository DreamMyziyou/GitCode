//
// Created by WeslyChen on 2024/1/25.
//

#include "VulkanSwapChainWrapper.h"

#include "VulkanManager.h"

using namespace std;

void VulkanSwapChainWrapper::CreateResource()
{
    CreateSwapChain();
    CreateImageViews();
    CreateFrameBuffers();
}

void VulkanSwapChainWrapper::DestroyResource()
{
    auto device = VulkanManager::instance()->GetDevice();

    for (auto framebuffer : mSwapChainFrameBuffers)
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    mSwapChainFrameBuffers.clear();

    for (auto imageView : mSwapChainImageViews)
        vkDestroyImageView(device, imageView, nullptr);
    mSwapChainImageViews.clear();

    mSwapChainImages.clear();

    vkDestroySwapchainKHR(device, mSwapChain, nullptr);
    mSwapChain = nullptr;
}

void VulkanSwapChainWrapper::CreateSwapChain()
{
    auto surfaceWrapper = VulkanManager::instance()->GetSurfaceWrapper();
    auto expectFormat = surfaceWrapper->GetExpectSurfaceFormat();
    auto expectSwapExtent = surfaceWrapper->GetExpectSwapChainExtent();
    auto expectBufferCount = surfaceWrapper->GetExpectSwapChainBufferCount();
    auto presentMode = surfaceWrapper->GetExpectPresentMode();
    auto& surfaceCapabilities = surfaceWrapper->GetSurfaceCapabilities();

    auto deviceWrapper = VulkanManager::instance()->GetDeviceWrapper();
    auto physicalDevice = deviceWrapper->GetPhysicalDevice();
    auto device = deviceWrapper->GetLogicDevice();

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surfaceWrapper->GetSurface();
    createInfo.minImageCount = expectBufferCount;
    createInfo.imageFormat = expectFormat.format;
    createInfo.imageColorSpace = expectFormat.colorSpace;
    createInfo.imageExtent = expectSwapExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    auto indices = surfaceWrapper->FindQueueFamilies(physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;  // Optional
        createInfo.pQueueFamilyIndices = nullptr;  // Optional
    }

    createInfo.preTransform = surfaceCapabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapChain;
    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "failed to create swap chain!");

    mSwapChain = swapChain;

    vkGetSwapchainImagesKHR(device, swapChain, &expectBufferCount, nullptr);
    mSwapChainImages.resize(expectBufferCount);
    vkGetSwapchainImagesKHR(device, swapChain, &expectBufferCount, mSwapChainImages.data());

    mSwapChainImageFormat = expectFormat.format;
    mSwapChainExtent = expectSwapExtent;
}

VkFramebuffer VulkanSwapChainWrapper::GetBuffer(size_t bufferIndex) const
{
    if (bufferIndex >= mSwapChainFrameBuffers.size())
        return nullptr;

    return mSwapChainFrameBuffers[bufferIndex];
}

void VulkanSwapChainWrapper::CreateImageViews()
{
    if (mSwapChainImages.empty())
        return;

    mSwapChainImageViews.resize(mSwapChainImages.size());

    for (size_t i = 0; i < mSwapChainImages.size(); i++)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = mSwapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = mSwapChainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(VulkanManager::instance()->GetDevice(), &createInfo, nullptr, &mSwapChainImageViews[i]) != VK_SUCCESS)
            Logger::LogFatal("VulkanRender", "failed to create image views!");
    }
}

void VulkanSwapChainWrapper::CreateFrameBuffers()
{
    if (mSwapChainImageViews.empty())
        return;

    mSwapChainFrameBuffers.resize(mSwapChainImageViews.size());

    for (size_t i = 0; i < mSwapChainImageViews.size(); i++)
    {
        VkImageView attachments[] = {mSwapChainImageViews[i]};
        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = VulkanManager::instance()->GetRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = mSwapChainExtent.width;
        framebufferInfo.height = mSwapChainExtent.height;
        framebufferInfo.layers = 1;
        if (vkCreateFramebuffer(VulkanManager::instance()->GetDevice(), &framebufferInfo, nullptr, &mSwapChainFrameBuffers[i]) != VK_SUCCESS)
            Logger::LogFatal("VulkanRender", "failed to create framebuffer!");
    }
}
