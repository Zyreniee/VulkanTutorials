#pragma once

#include "lve_device.hpp"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>

namespace lve {

    class LveModel {
    public:
        struct Vertex {
            glm::vec2 position;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions() {
                VkVertexInputBindingDescription binding{};
                binding.binding = 0;
                binding.stride = sizeof(Vertex);
                binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
                return { binding };
            }

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
                VkVertexInputAttributeDescription pos{};
                pos.binding = 0;
                pos.location = 0;                           // vertex shader'daki 'layout(location=0)'
                pos.format = VK_FORMAT_R32G32_SFLOAT;     // glm::vec2 için DOÐRU format
                pos.offset = offsetof(Vertex, position);
                return { pos };
            }
        };

        LveModel(lveDevice& device, const std::vector<Vertex>& vertices);
        ~LveModel();

        LveModel(const LveModel&) = delete;
        LveModel& operator=(const LveModel&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        lveDevice& device;
        VkBuffer vertexBuffer = VK_NULL_HANDLE;           // güvenli baþlangýç
        VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
        uint32_t vertexCount = 0;
    };

} // namespace lve
