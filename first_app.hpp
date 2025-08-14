#pragma once
#include "lve_window.hpp"
#include "lve_pipeline.hpp"

namespace lve {
	// FirstApp sýnýfý, uygulamanýn ana yapýsýný temsil eder
	class FirstApp {
	public:
		static constexpr int WIDTH = 800; // Varsayýlan pencere geniþliði
		static constexpr int HEIGHT = 600; // Varsayýlan pencere yüksekliði
		void run(); // Uygulamanýn ana döngüsünü baþlatan fonksiyon

	private:
		lveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" }; // Uygulamanýn pencere nesnesi
		// Diðer üyeler burada tanýmlanabilir (ör: Vulkan instance, device, swapchain, vs.)
		LvePipeline lvePipeline{ "Shaders/simple_shader.vert.spv", "Shaders/simple_shader.frag.spv" }; // Vulkan pipeline nesnesi
	};
}//namespace lve