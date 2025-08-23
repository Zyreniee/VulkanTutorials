#pragma once

#include "lve_device.hpp"
#include "lve_model.hpp"

#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace lve {

    struct PipelineConfigInfo {
        PipelineConfigInfo() = default;
        PipelineConfigInfo(const PipelineConfigInfo&) = delete;
        PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

        // Vertex input
        std::vector<VkVertexInputBindingDescription> bindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

        // Dynamic states
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;

        // Viewport
        VkPipelineViewportStateCreateInfo viewportInfo;

        // Input Assembly
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;

        // Rasterizer
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;

        // Multisampling
        VkPipelineMultisampleStateCreateInfo multisampleInfo;

        // Color blending
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;

        // Depth & stencil
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;

        // Pipeline layout / render pass
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
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

        LvePipeline(const LvePipeline&) = delete;
        LvePipeline& operator=(const LvePipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

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
