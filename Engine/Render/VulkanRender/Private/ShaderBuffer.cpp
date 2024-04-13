//
// Created by WeslyChen on 2024/2/4.
//
#include "ShaderBuffer.h"

#include "UniformBuffer.h"
#include "VulkanComponent.h"

using namespace std;

ShaderBuffer::ShaderBuffer()
{
    CreateUniformBuffers();
}

ShaderBuffer::~ShaderBuffer()
{
    ReleaseBuffer();
}

void ShaderBuffer::OnMeshUpdate(const MeshComponent& mesh)
{
    CreateVertexBuffer(mesh.vertices);

    mIndexSize = mesh.indices.size();

    CreateIndexBuffer(mesh.indices);
}

void ShaderBuffer::CreateVertexBuffer(const std::vector<Vertex>& vertices)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void* data = nullptr;
    vkMapMemory(deviceComponent->mLogicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(deviceComponent->mLogicDevice, stagingBufferMemory);

    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 mVertexBuffer,
                 mVertexBufferMemory);

    CopyBuffer(stagingBuffer, mVertexBuffer, bufferSize);

    vkDestroyBuffer(deviceComponent->mLogicDevice, stagingBuffer, nullptr);
    vkFreeMemory(deviceComponent->mLogicDevice, stagingBufferMemory, nullptr);
}

void ShaderBuffer::CreateIndexBuffer(const vector<uint16>& indices)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void* data = nullptr;
    vkMapMemory(deviceComponent->mLogicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(deviceComponent->mLogicDevice, stagingBufferMemory);

    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 mIndexBuffer,
                 mIndexBufferMemory);

    CopyBuffer(stagingBuffer, mIndexBuffer, bufferSize);

    vkDestroyBuffer(deviceComponent->mLogicDevice, stagingBuffer, nullptr);
    vkFreeMemory(deviceComponent->mLogicDevice, stagingBufferMemory, nullptr);
}

void ShaderBuffer::CreateUniformBuffers()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    mUniformBuffers.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    mUniformBuffersMemory.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    mUniformBuffersMapped.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; i++)
    {
        CreateBuffer(bufferSize,
                     VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     mUniformBuffers[i],
                     mUniformBuffersMemory[i]);

        vkMapMemory(deviceComponent->mLogicDevice, mUniformBuffersMemory[i], 0, bufferSize, 0, &mUniformBuffersMapped[i]);
    }
}

void ShaderBuffer::CreateBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    auto vkResult = vkCreateBuffer(deviceComponent->mLogicDevice, &bufferInfo, nullptr, &buffer);
    if (vkResult != VK_SUCCESS)
        return;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(deviceComponent->mLogicDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = deviceComponent->FindMemoryType(memRequirements.memoryTypeBits, properties);

    vkResult = vkAllocateMemory(deviceComponent->mLogicDevice, &allocInfo, nullptr, &bufferMemory);
    if (vkResult != VK_SUCCESS)
        return;

    vkBindBufferMemory(deviceComponent->mLogicDevice, buffer, bufferMemory, 0);
}

void ShaderBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = deviceComponent->mCommandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(deviceComponent->mLogicDevice, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;  // Optional
    copyRegion.dstOffset = 0;  // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    vkQueueSubmit(deviceComponent->mGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(deviceComponent->mGraphicsQueue);

    vkFreeCommandBuffers(deviceComponent->mLogicDevice, deviceComponent->mCommandPool, 1, &commandBuffer);
}

void ShaderBuffer::ReleaseBuffer()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->mPhysicalDevice || !deviceComponent->mLogicDevice)
        return;

    if (mVertexBuffer)
    {
        vkDestroyBuffer(deviceComponent->mLogicDevice, mVertexBuffer, nullptr);
        mVertexBuffer = nullptr;
    }

    if (mVertexBufferMemory)
    {
        vkFreeMemory(deviceComponent->mLogicDevice, mVertexBufferMemory, nullptr);
        mVertexBufferMemory = nullptr;
    }

    if (mIndexBuffer)
    {
        vkDestroyBuffer(deviceComponent->mLogicDevice, mIndexBuffer, nullptr);
        mIndexBuffer = nullptr;
    }

    if (mIndexBufferMemory)
    {
        vkFreeMemory(deviceComponent->mLogicDevice, mIndexBufferMemory, nullptr);
        mIndexBufferMemory = nullptr;
    }

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroyBuffer(deviceComponent->mLogicDevice, mUniformBuffers[i], nullptr);
        vkFreeMemory(deviceComponent->mLogicDevice, mUniformBuffersMemory[i], nullptr);
    }
    mUniformBuffers.clear();
    mUniformBuffersMemory.clear();
    mUniformBuffersMapped.clear();
}
