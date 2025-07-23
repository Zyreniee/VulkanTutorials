#include "lve_pipeline.hpp"
#include <vector>	
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vulkan/vulkan.h>

using namespace std;

namespace lve {

	LvePipeline::LvePipeline(
		const string& vertFilePath, const string& fragFilePath) {
		createGraphicsPipeline(vertFilePath, fragFilePath);
	}

	vector<char> LvePipeline::readFile(const string& filePath) {
		ifstream file{ filePath, ios::ate | ios::binary };
		if (!file.is_open()) {
			throw runtime_error("failed to open file: " + filePath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void LvePipeline::createGraphicsPipeline(
		const string& vertFilePath, const string& fragFilePath) {

		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		cout << "Vertex Shader Code Size: " << vertCode.size() << endl;
		cout << "Fragment Shader Code Size: " << fragCode.size() << endl;
	}

	VkShaderModule LvePipeline::createShaderModule(const vector<char>& code) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(VK_NULL_HANDLE, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
			throw runtime_error("failed to create shader module");
		}

		return shaderModule;
	}

}
