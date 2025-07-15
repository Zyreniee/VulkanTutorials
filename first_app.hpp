#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"

namespace lve {
	class FirstApp {
	
	
	private:
		lveWindow lveWindow{ WIDTH , HEIGHT,"Hello Vulkan!" };
		LvePipeline lvePipeline{ "shaders/simple_shader.vert.spv","shaders/simple_shader.frag.spv" };


	public:
		static constexpr int HEIGHT = 600;
		static constexpr int WIDTH = 800;
		

		void run();
		
	};
} //namespace lve