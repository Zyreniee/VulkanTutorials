#pragma once

#include "lve_device.hpp"
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace lve {

    struct PipelineConfigInfo {
        // Ýleride pipeline yapýlandýrma ayarlarýný buraya ekleyeceðiz
    };

    class LvePipeline {
    public:
        LvePipeline(
            lveDevice& device,
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);

        ~LvePipeline() {
            if (vertShaderModule != VK_NULL_HANDLE) {
                vkDestroyShaderModule(device.device(), vertShaderModule, nullptr);
            }
            if (fragShaderModule != VK_NULL_HANDLE) {
                vkDestroyShaderModule(device.device(), fragShaderModule, nullptr);
            }
            if (graphicsPipeline != VK_NULL_HANDLE) {
                vkDestroyPipeline(device.device(), graphicsPipeline, nullptr);
            }
        }

        LvePipeline(const LvePipeline&) = delete;
        LvePipeline& operator=(const LvePipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipeline(
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        lveDevice& device;
        VkPipeline      graphicsPipeline{ VK_NULL_HANDLE };
        VkShaderModule  vertShaderModule{ VK_NULL_HANDLE };
        VkShaderModule  fragShaderModule{ VK_NULL_HANDLE };

    };

} // namespace lve
// Compare this snippet from lve_pipeline.cpp: