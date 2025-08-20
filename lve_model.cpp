#include "lve_model.hpp"
//std
#include <cassert>
namespace lve {
	LveModel::LveModel(lveDevice& device, const std::vector<Vertex>& vertices) : lveDevice{device} {
		createVertexBuffers(vertices);
	}
	LveModel::~LveModel() {
		vkDestroyBuffer(lveDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(lveDevice.device(), vertexBufferMemory, nullptr);
	}
	void LveModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
	}
}