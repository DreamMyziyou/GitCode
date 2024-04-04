//
// Created by WeslyChen on 2024/1/21.
//

#include <vector>

#include "VulkanComponent.h"
#include "VulkanInstanceSystem.h"

using namespace std;

static const std::vector<const char*> gValidationLayers = {"VK_LAYER_KHRONOS_validation"};
#ifdef NDEBUG
constexpr bool ENABLE_VALIDATION_LAYERS = false;
#else
constexpr bool ENABLE_VALIDATION_LAYERS = true;
#endif

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                    void* pUserData)
{
    Logger::LogError("VulkanRender", pCallbackData->pMessage);
    return VK_FALSE;
}

void VulkanInstanceSystem::OnInit()
{
    auto center = VkRCenter::instance();
    if (center->vulkanEntity != entt::null)
        return;

    center->vulkanEntity = center->world.create();
    if (center->world.try_get<VulkanInstanceComponent>(center->vulkanEntity))
        return;
    auto& vulkanComponent = center->world.emplace<VulkanInstanceComponent>(center->vulkanEntity);

    // app info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "WorkEngineGame";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "WorkEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = nullptr;

    // instance base info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // check whether apply validation layer
    if (ENABLE_VALIDATION_LAYERS)
    {
        if (CheckValidationLayer())
            vulkanComponent.applyValidationLayer = true;
        else
            Logger::LogError("VulkanRender", "Validation layers requested, but not available!");
    }

    // set extensions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (vulkanComponent.applyValidationLayer)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // set vaildation layer
    if (vulkanComponent.applyValidationLayer)
    {
        VkDebugUtilsMessengerCreateInfoEXT debugInfo;
        BuildDebugInfoTo(debugInfo);
        createInfo.enabledLayerCount = static_cast<uint32_t>(gValidationLayers.size());
        createInfo.ppEnabledLayerNames = gValidationLayers.data();
        createInfo.pNext = &debugInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    // create instance
    auto vkResult = vkCreateInstance(&createInfo, nullptr, &vulkanComponent.instance);
    if (vkResult != VK_SUCCESS)
        Logger::LogFatal("VulkanRender", "Init Vulkan failed");
    else
        Logger::LogInfo("VulkanRender", "Init Vulkan success.");

    // build debug messenger
    BuildDebugMessenger();

    // check extension
    CheckInstanceExtension();
}

void VulkanInstanceSystem::OnDestroy()
{
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (vulkanComponent == nullptr)
        return;

    if (vulkanComponent->applyValidationLayer)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vulkanComponent->instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(vulkanComponent->instance, vulkanComponent->debugMessenger, nullptr);
    }

    vkDestroyInstance(vulkanComponent->instance, nullptr);
    VkRCenter::instance()->world.destroy(VkRCenter::instance()->vulkanEntity);
    VkRCenter::instance()->vulkanEntity = entt::null;

    Logger::LogInfo("VulkanRender", "Uninit Vulkan.");
}

void VulkanInstanceSystem::OnUpdate() {}

void VulkanInstanceSystem::CheckInstanceExtension() const
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    String logMsg = "available extensions:\n";
    for (const auto& extension : extensions)
    {
        logMsg += '\t';
        logMsg += extension.extensionName;
        logMsg += '\n';
    }
    Logger::LogInfo("VulkanRender", logMsg);
}

bool VulkanInstanceSystem::CheckValidationLayer() const
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : gValidationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

void VulkanInstanceSystem::BuildDebugInfoTo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
{
    debugCreateInfo = {};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = DebugCallback;
    debugCreateInfo.pUserData = nullptr;  // Optional
}

void VulkanInstanceSystem::BuildDebugMessenger()
{
    auto vulkanComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanInstanceComponent>();
    if (vulkanComponent == nullptr)
        return;
    if (!vulkanComponent->applyValidationLayer)
        return;

    VkDebugUtilsMessengerCreateInfoEXT debugInfo;
    BuildDebugInfoTo(debugInfo);

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vulkanComponent->instance, "vkCreateDebugUtilsMessengerEXT");
    func(vulkanComponent->instance, &debugInfo, nullptr, &vulkanComponent->debugMessenger);
}
