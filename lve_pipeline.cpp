#include "lve_pipeline.hpp"
#include "lve_device.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace lve {

    LvePipeline::LvePipeline(
        lveDevice& device,
        const std::string& vertFilepath,
        const std::string& fragFilepath,
        const PipelineConfigInfo& configInfo)
        : device{ device } {

        createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);

    }

   
    std::vector<char> LvePipeline::readFile(const std::string& filepath) {
    
        std::ifstream file{ filepath, std::ios::ate | std::ios::binary };
        
        if (!file.is_open()) {
        
            throw std::runtime_error("failed to open file: " + filepath);
        }

      
        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }

    void LvePipeline::createGraphicsPipeline(
        const std::string& vertFilepath,
        const std::string& fragFilepath,
        const PipelineConfigInfo& configInfo) {

        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex shader code size: " << vertCode.size() << " bytes\n";
        std::cout << "Fragment shader code size: " << fragCode.size() << " bytes\n";

        // Shader modüllerini oluþtur
        createShaderModule(vertCode, &vertShaderModule);
        createShaderModule(fragCode, &fragShaderModule);

        // TODO: Vulkan graphics pipeline oluþturma kodu buraya gelecek
        (void)configInfo; // kullanýlmadý uyarýsýný susturmak için
    }


    void LvePipeline::createShaderModule(
       const std::vector<char>& code,
        VkShaderModule* shaderModule) {

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        // lveDevice yerine artýk üye 'device' kullanýlýyor
        if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module");
        }   
    }

    PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t ) {
        PipelineConfigInfo configInfo;

        return configInfo;
    }

} // namespace lve
// Not: Bu kod, LvePipeline sýnýfýnýn temel iþlevselliðini içerir.