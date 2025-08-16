#pragma once

#include "lve_device.hpp"
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace lve {

    struct PipelineConfigInfo {
        // Viewport & Scissor
        VkViewport viewport{};
        VkRect2D scissor{};
        VkPipelineViewportStateCreateInfo viewportInfo{};

        // Input Assembly
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};

        // Rasterizer
        VkPipelineRasterizationStateCreateInfo rasterizationInfo{};

        // Multisampling
        VkPipelineMultisampleStateCreateInfo multisampleInfo{};

        // Color blending
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        VkPipelineColorBlendStateCreateInfo colorBlendInfo{};

        // Depth & Stencil
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};

        // Pipeline layout / render pass bilgileri
        VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
        VkRenderPass renderPass = VK_NULL_HANDLE;
        uint32_t subpass = 0;
    };

    class LvePipeline {
    public:
        LvePipeline(
            lveDevice& device,
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);

        ~LvePipeline();

        // Copy constructor ve assignment engellendi
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
        VkPipeline graphicsPipeline{ VK_NULL_HANDLE };
        VkShaderModule vertShaderModule{ VK_NULL_HANDLE };
        VkShaderModule fragShaderModule{ VK_NULL_HANDLE };
    };

} // namespace lve
