#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_window.hpp"

//std
#include <memory>
#include <vector>

namespace lve {

    class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp &operator=(const FirstApp &) = delete;

        void run();

    private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

        lveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
        lveDevice device{ lveWindow }; // Vulkan cihazýný oluþtur

		LveSwapChain lveSwapChain{ device, lveWindow.getExtent() }; 

        PipelineConfigInfo config = LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT);
		std::unique_ptr<LvePipeline> lvePipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
    };

} // namespace lve
