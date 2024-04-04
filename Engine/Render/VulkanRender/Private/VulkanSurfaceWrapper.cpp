//
// Created by WeslyChen on 2024/1/28.
//
#include "VulkanSurfaceWrapper.h"

#include <algorithm>
#include <limits>

#include "GlfwWindowComponent.h"
#include "VulkanComponent.h"
#include "VulkanManager.h"

using namespace std;

void VulkanSurfaceWrapper::OnInit()
{
    auto windowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (!windowComponent || !windowComponent->window)
        return;
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (!vulkanComponent)
        return;

    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(windowComponent->window);
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = nullptr;
    if (vkCreateWin32SurfaceKHR(vulkanComponent->instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
        return Logger::LogFatal("VulkanRender", "Failed to create window surface!");
    else
        mSurface = surface;
}

void VulkanSurfaceWrapper::OnDestroy()
{
    if (nullptr == mSurface)
        return;
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (!vulkanComponent)
        return;

    vkDestroySurfaceKHR(vulkanComponent->instance, mSurface, nullptr);
    mSurface = nullptr;
}

void VulkanSurfaceWrapper::OnUpdate() {}

VulkanSurfaceWrapper::QueueFamilyIndices VulkanSurfaceWrapper::FindQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int32 i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (indices.IsComplete())
            break;

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, mSurface, &presentSupport);
        if (presentSupport)
            indices.presentFamily = i;

        i++;
    }

    return indices;
}

VulkanSurfaceWrapper::SwapChainSupportDetails VulkanSurfaceWrapper::QuerySwapChainSupport(VkPhysicalDevice device) const
{
    SwapChainSupportDetails details;

    auto surface = mSurface;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

VkSurfaceFormatKHR VulkanSurfaceWrapper::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const
{
    for (const auto& availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return availableFormat;
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanSurfaceWrapper::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const
{
    for (const auto& availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSurfaceWrapper::ChooseSwapExtent(VkPhysicalDevice device, const VkSurfaceCapabilitiesKHR& capabilities) const
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        return capabilities.currentExtent;

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, mSurface, &surfaceCapabilities);

    VkExtent2D actualExtent = surfaceCapabilities.currentExtent;

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

void VulkanSurfaceWrapper::OnUpdate(VkPhysicalDevice device)
{
    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
    mSurfaceCapabilities = swapChainSupport.capabilities;
    mExpectSurfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    mExpectPresentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    mExpectSwapChainExtent = ChooseSwapExtent(device, swapChainSupport.capabilities);
    uint32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        imageCount = swapChainSupport.capabilities.maxImageCount;
    mExpectSwapChainBufferCount = imageCount;
}
