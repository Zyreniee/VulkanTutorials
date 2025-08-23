#include "first_app.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_window.hpp"
#include "lve_model.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <array>
#include <stdexcept>
#include <memory>
#include <cstring>
#include <cmath>

namespace lve {

    struct SimplePushConstantData {
        glm::vec2 offset;
        alignas(16) glm::vec3 color;
    };

    const std::vector<float> vertices = {
        0.0f, -0.5f,
        0.5f, 0.5f,
       -0.5f, 0.5f
    };

    FirstApp::FirstApp() {
        loadModels();
        createVertexBuffer();
        createPipelineLayout();

        lveSwapChain = std::make_unique<LveSwapChain>(device, lveWindow.getExtent());
        createPipeline();
        createCommandBuffers();

        for (size_t i = 0; i < commandBuffers.size(); i++)
            recordCommandBuffer(static_cast<int>(i));
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
        std::vector<LveModel::Vertex> modelVertices{
            {{0.0f, -0.5f},{1.0f,0.0f,0.0f}},
            {{0.5f, 0.5f},{0.0f,1.0f,0.0f}},
            {{-0.5f, 0.5f},{0.0f,0.0f,1.0f}}
        };
        lveModel = std::make_unique<LveModel>(device, modelVertices);
    }

#pragma region Pipeline & CommandBuffer Functions

    void FirstApp::createPipelineLayout() {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
            throw std::runtime_error("failed to create pipeline layout!");
    }

    void FirstApp::createPipeline() {
        assert(lveSwapChain && pipelineLayout);

        PipelineConfigInfo pipelineConfig{};
        LvePipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = lveSwapChain->getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;

        lvePipeline = std::make_unique<LvePipeline>(
            device,
            "Shaders/simple_shader.vert.spv",
            "Shaders/simple_shader.frag.spv",
            pipelineConfig
        );
    }

    void FirstApp::recreateSwapChain() {
        auto extent = lveWindow.getExtent();
        while (extent.width == 0 || extent.height == 0) glfwWaitEvents(), extent = lveWindow.getExtent();
        vkDeviceWaitIdle(device.device());

        if (!lveSwapChain)
            lveSwapChain = std::make_unique<LveSwapChain>(device, extent);
        else {
            lveSwapChain = std::make_unique<LveSwapChain>(device, extent, std::move(lveSwapChain));
            if (lveSwapChain->imageCount() != commandBuffers.size()) {
                freeCommandBuffers();
                createCommandBuffers();
            }
        }

        createPipeline();

        for (size_t i = 0; i < commandBuffers.size(); i++)
            recordCommandBuffer(static_cast<int>(i));
    }

    void FirstApp::createCommandBuffers() {
        commandBuffers.resize(lveSwapChain->imageCount());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
            throw std::runtime_error("failed to allocate command buffers!");
    }

    void FirstApp::freeCommandBuffers() {
        if (!commandBuffers.empty()) {
            vkFreeCommandBuffers(device.device(), device.getCommandPool(),
                static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
            commandBuffers.clear();
        }
    }

    void FirstApp::recordCommandBuffer(int imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
            throw std::runtime_error("failed to begin recording command buffer!");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = lveSwapChain->getRenderPass();
        renderPassInfo.framebuffer = lveSwapChain->getFrameBuffer(imageIndex);
        renderPassInfo.renderArea.offset = { 0,0 };
        renderPassInfo.renderArea.extent = lveSwapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { {0.01f,0.01f,0.01f,1.0f} };
        clearValues[1].depthStencil = { 1.0f,0 };
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{ 0.0f,0.0f,
                            static_cast<float>(lveSwapChain->getSwapChainExtent().width),
                            static_cast<float>(lveSwapChain->getSwapChainExtent().height),
                            0.0f,1.0f };
        vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);

        VkRect2D scissor{ {0,0}, lveSwapChain->getSwapChainExtent() };
        vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

        lvePipeline->bind(commandBuffers[imageIndex]);
        lveModel->bind(commandBuffers[imageIndex]);

        for (int j = 0; j < 4; j++) {
            SimplePushConstantData push{};
            push.offset = { 0.0f,-0.4f + j * 0.25f };
            push.color = { 0.0f,0.0f,0.2f + 0.2f * j };
            vkCmdPushConstants(commandBuffers[imageIndex], pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0, sizeof(SimplePushConstantData), &push);
            lveModel->draw(commandBuffers[imageIndex]);
        }

        vkCmdEndRenderPass(commandBuffers[imageIndex]);

        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
            throw std::runtime_error("failed to record command buffer!");
    }

#pragma endregion

#pragma region Draw Frame

    void FirstApp::drawFrame() {
        uint32_t imageIndex;
        auto result = lveSwapChain->acquireNextImage(&imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) { recreateSwapChain(); return; }
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) throw std::runtime_error("failed to acquire swap chain image!");

        float x_offset = fmod(static_cast<float>(glfwGetTime()) * 0.5f, 2.0f) - 1.0f;

        // Command buffer yeniden record
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
            throw std::runtime_error("failed to begin recording command buffer!");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = lveSwapChain->getRenderPass();
        renderPassInfo.framebuffer = lveSwapChain->getFrameBuffer(imageIndex);
        renderPassInfo.renderArea.offset = { 0,0 };
        renderPassInfo.renderArea.extent = lveSwapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { {0.01f,0.01f,0.01f,1.0f} };
        clearValues[1].depthStencil = { 1.0f,0 };
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{ 0.0f,0.0f,
                            static_cast<float>(lveSwapChain->getSwapChainExtent().width),
                            static_cast<float>(lveSwapChain->getSwapChainExtent().height),
                            0.0f,1.0f };
        vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);

        VkRect2D scissor{ {0,0}, lveSwapChain->getSwapChainExtent() };
        vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

        lvePipeline->bind(commandBuffers[imageIndex]);
        lveModel->bind(commandBuffers[imageIndex]);

        for (int j = 0; j < 4; j++) {
            SimplePushConstantData push{};
            push.offset = { x_offset,-0.4f + j * 0.25f };
            push.color = { 0.0f,0.0f,0.2f + 0.2f * j };
            vkCmdPushConstants(commandBuffers[imageIndex], pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0, sizeof(SimplePushConstantData), &push);
            lveModel->draw(commandBuffers[imageIndex]);
        }

        vkCmdEndRenderPass(commandBuffers[imageIndex]);

        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
            throw std::runtime_error("failed to record command buffer!");

        result = lveSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || lveWindow.wasWindowResized()) {
            lveWindow.resetWindowResizedFlag();
            recreateSwapChain();
            return;
        }
        if (result != VK_SUCCESS) throw std::runtime_error("failed to present swap chain image!");
    }

#pragma endregion

#pragma region Vertex Buffer

    void FirstApp::createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(float) * vertices.size();
        device.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vertexBuffer, vertexBufferMemory);
        void* data;
        vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(device.device(), vertexBufferMemory);
    }

#pragma endregion

} // namespace lve
