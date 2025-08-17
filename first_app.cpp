#include "first_app.hpp"

//std
#include <iostream>
#include <stdexcept>

namespace lve {

	// Uygulamanýn ana döngüsü: pencere kapanana kadar çalýþýr
	void FirstApp::run() {
		while (!lveWindow.shouldClose()) {
			glfwPollEvents(); // GLFW olaylarýný iþle
			// Burada genellikle çizim, giriþ iþlemleri vs. yapýlýr
			// Örneðin:
			// drawFrame();
			// handleInput();
		}
	}
#pragma region CreatePipeline etc. Functions
	void FirstApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0; // Descriptor set layout'larý eklenebilir
		pipelineLayoutInfo.pSetLayouts = nullptr;// Push constant'lar eklenebilir
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}
	void FirstApp::createPipeline() {
	auto pipelineConfig =
		LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
	    pipelineConfig.renderPass = lveSwapChain.getRenderPass();
	}
#pragma endregion
}