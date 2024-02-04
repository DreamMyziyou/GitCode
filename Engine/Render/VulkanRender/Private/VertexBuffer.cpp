//
// Created by WeslyChen on 2024/2/4.
//
#include "VertexBuffer.h"

#include "VulkanManager.h"

using namespace std;

VertexBuffer::~VertexBuffer()
{
    ReleaseBuffer();
}

void VertexBuffer::OnMeshUpdate(const MeshComponent& mesh)
{
    CreateBuffer(mesh.vertices);
    if (!mVertexBuffer || !mVertexBufferMemory)
        return;
}

void VertexBuffer::CreateBuffer(const std::vector<Vertex>& vertices)
{
    ReleaseBuffer();

    auto deviceWrapper = VulkanManager::instance()->GetDeviceWrapper();
    auto device = deviceWrapper->GetLogicDevice();

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(vertices[0]) * vertices.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    auto vkResult = vkCreateBuffer(device, &bufferInfo, nullptr, &mVertexBuffer);
    if (vkResult != VK_SUCCESS)
        return;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, mVertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex =
            deviceWrapper->FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    vkResult = vkAllocateMemory(device, &allocInfo, nullptr, &mVertexBufferMemory);
    if (vkResult != VK_SUCCESS)
        return;

    vkBindBufferMemory(device, mVertexBuffer, mVertexBufferMemory, 0);

    void* data = nullptr;
    vkMapMemory(device, mVertexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(device, mVertexBufferMemory);
}

void VertexBuffer::ReleaseBuffer()
{
    auto device = VulkanManager::instance()->GetDevice();

    if (mVertexBuffer)
    {
        vkDestroyBuffer(device, mVertexBuffer, nullptr);
        mVertexBuffer = nullptr;
    }

    if (mVertexBufferMemory)
    {
        vkFreeMemory(device, mVertexBufferMemory, nullptr);
        mVertexBufferMemory = nullptr;
    }
}
