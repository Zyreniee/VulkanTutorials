#include "first_app.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_window.hpp"

// std
#include <array>
#include <stdexcept>
#include <memory>
#include <cstring>

namespace lve {

    // Basit üçgen verisi (x, y)
    const std::vector<float> vertices = {
        0.0f, -0.5f,  // Alt
        0.5f, 0.5f,   // Sað üst
       -0.5f, 0.5f    // Sol üst
    };

    FirstApp::FirstApp() {
        loadModels();
        createVertexBuffer();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    FirstApp::~FirstApp() {
        vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
        vkFreeMemory(device.device(), vertexBufferMemory, nullptr);
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void FirstApp::run() {
        while (!lveWindow.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(device.device());
    }

    void FirstApp::loadModels() {
        std::vector<LveModel::Vertex> vertices{
            {{0.0f, -0.5f},{1.0f,0.0f,0.0f}},
            {{0.5f, 0.5f},{0.0f,1.0f,0.0f}},
            {{-0.5f, 0.5f},{ 0.0f,0.0f,1.0f }} };
        lveModel = std::make_unique<LveModel>(device, vertices);
    }

#pragma region Pipeline & CommandBuffer Functions

    void FirstApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void FirstApp::createPipeline() {
        auto pipelineConfig = LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
        pipelineConfig.renderPass = lveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;

        // Basit üçgen çizimi, sadece pozisyon kullanýyor
        pipelineConfig.bindingDescriptions.clear();
        pipelineConfig.attributeDescriptions.clear();

        VkVertexInputBindingDescription binding{};
        binding.binding = 0;
        binding.stride = sizeof(float) * 2; // x, y
        binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        pipelineConfig.bindingDescriptions.push_back(binding);

        VkVertexInputAttributeDescription posAttr{};
        posAttr.binding = 0;
        posAttr.location = 0;
        posAttr.format = VK_FORMAT_R32G32_SFLOAT;
        posAttr.offset = 0;
        pipelineConfig.attributeDescriptions.push_back(posAttr);

        lvePipeline = std::make_unique<LvePipeline>(
            device,
            "Shaders/simple_shader.vert.spv",
            "Shaders/simple_shader.frag.spv",
            pipelineConfig
        );
    }

    void FirstApp::createCommandBuffers() {
        commandBuffers.resize(lveSwapChain.imageCount());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (int i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = lveSwapChain.getRenderPass();
            renderPassInfo.framebuffer = lveSwapChain.getFrameBuffer(i);
            renderPassInfo.renderArea.offset = { 0,0 };
            renderPassInfo.renderArea.extent = lveSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            lvePipeline->bind(commandBuffers[i]);
            lveModel->bind(commandBuffers[i]); // Model önce bind edilmeli
            lveModel->draw(commandBuffers[i]);

            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }

    void FirstApp::drawFrame() {
        uint32_t imageIndex;
        auto result = lveSwapChain.acquireNextImage(&imageIndex);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = lveSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }

#pragma endregion

#pragma region Vertex Buffer Functions

    void FirstApp::createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(float) * vertices.size();

        device.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vertexBuffer,
            vertexBufferMemory
        );

        void* data;
        vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(device.device(), vertexBufferMemory);
    }

#pragma endregion

} // namespace lve
