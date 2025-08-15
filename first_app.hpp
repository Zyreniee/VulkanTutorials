#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_window.hpp"

namespace lve {

    class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        lveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
        lveDevice device{ lveWindow }; // Vulkan cihazýný oluþtur

        PipelineConfigInfo config = LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT);
        LvePipeline pipeline{ device,
        "Shaders/simple_shader.vert.spv",
        "Shaders/simple_shader.frag.spv",
        LvePipeline::defaultPipelineConfigInfo(WIDTH , HEIGHT)};
    };

} // namespace lve
