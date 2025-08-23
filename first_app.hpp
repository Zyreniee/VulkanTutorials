    #pragma once

    #include "lve_pipeline.hpp"
    #include "lve_device.hpp"
    #include "lve_swap_chain.hpp"
    #include "lve_window.hpp"
    #include "lve_model.hpp"

    // std
    #include <memory>
    #include <vector>
    #include <vulkan/vulkan.h>

    namespace lve {

        class FirstApp {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            FirstApp();
            ~FirstApp();

            FirstApp(const FirstApp&) = delete;
            FirstApp& operator=(const FirstApp&) = delete;

            void run();

        private:
		    void loadModels();
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
			void freeCommandBuffers();
            void drawFrame();
		    void recreateSwapChain();
		    void recordCommandBuffer(int imagendex);
            void createVertexBuffer();

            lveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
            lveDevice device{ lveWindow };
            std::unique_ptr<LveSwapChain> lveSwapChain;

            PipelineConfigInfo pipelineConfig;  // Boþ struct oluþtur, fonksiyonla dolduracaðýz

            std::unique_ptr<LvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
            std::unique_ptr<LveModel> lveModel;

            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
        };

    } // namespace lve
