//
// Created by WeslyChen on 2024/2/4.
//
#ifndef WORLDENGINE_MESHBUFFER_H
#define WORLDENGINE_MESHBUFFER_H

#include "Core/Geometry/MeshComponent.h"
#include "VulkanResource.h"

class MeshBuffer final
{
public:
    MeshBuffer() = default;
    ~MeshBuffer();
    MeshBuffer(const MeshBuffer&) = delete;
    MeshBuffer& operator=(const MeshBuffer&) = delete;

public:
    VkBuffer GetVertexBufferHandle() const { return mVertexBuffer; }
    VkBuffer GetIndexBufferHandle() const { return mIndexBuffer; }
    size_t GetIndexSize() const { return mIndexSize; }

    void OnMeshUpdate(const MeshComponent& mesh);

private:
    void CreateVertexBuffer(const std::vector<Vertex>& vertices);
    void CreateIndexBuffer(const std::vector<uint16>& indices);

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void ReleaseBuffer();

private:
    VkBuffer mVertexBuffer = nullptr;
    VkDeviceMemory mVertexBufferMemory = nullptr;

    size_t mIndexSize = 0;
    VkBuffer mIndexBuffer = nullptr;
    VkDeviceMemory mIndexBufferMemory = nullptr;
};

#endif  // WORLDENGINE_MESHBUFFER_H
