//
// Created by WeslyChen on 2024/2/4.
//
#ifndef WORLDENGINE_SHADERBUFFER_H
#define WORLDENGINE_SHADERBUFFER_H

#include "Core/Geometry/MeshComponent.h"
#include "VulkanResource.h"

class ShaderBuffer final
{
public:
    ShaderBuffer();
    ~ShaderBuffer();
    ShaderBuffer(const ShaderBuffer&) = delete;
    ShaderBuffer& operator=(const ShaderBuffer&) = delete;

public:
    VkBuffer GetVertexBufferHandle() const { return mVertexBuffer; }
    VkBuffer GetIndexBufferHandle() const { return mIndexBuffer; }
    size_t GetIndexSize() const { return mIndexSize; }
    const std::vector<VkBuffer>& GetUniformBuffer() const { return mUniformBuffers; }
    const std::vector<void*>& GetUniformBufferMapped() const { return mUniformBuffersMapped; }

    void OnMeshUpdate(const MeshComponent& mesh);

private:
    void CreateVertexBuffer(const std::vector<Vertex>& vertices);
    void CreateIndexBuffer(const std::vector<uint16>& indices);
    void CreateUniformBuffers();

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void ReleaseBuffer();

private:
    VkBuffer mVertexBuffer = nullptr;
    VkDeviceMemory mVertexBufferMemory = nullptr;

    size_t mIndexSize = 0;
    VkBuffer mIndexBuffer = nullptr;
    VkDeviceMemory mIndexBufferMemory = nullptr;

    std::vector<VkBuffer> mUniformBuffers;
    std::vector<VkDeviceMemory> mUniformBuffersMemory;
    std::vector<void*> mUniformBuffersMapped;
};

#endif  // WORLDENGINE_SHADERBUFFER_H
