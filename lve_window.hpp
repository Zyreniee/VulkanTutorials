#pragma once

#include <vulkan/vulkan.h>  // <<< EKLENDÝ
#include <GLFW/glfw3.h>
// <<< EKLENDÝ
#include <string>
#include <stdexcept>

namespace lve {
	class lveWindow
	{
	private:
	    int width = 800;
		int height = 600;
		bool framebufferResized = false;
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		
		void initWindow();
		GLFWwindow* window;

	public:
		lveWindow(int w, int h, std::string name);
		~lveWindow();
		
		std::string windowName;

		lveWindow(const lveWindow&) = delete;
		lveWindow& operator=(const lveWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }
		VkExtent2D getExtent() {return VkExtent2D{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };}

		bool wasWindowResized() { return framebufferResized; }
		void resetWindowResizedFlag() { framebufferResized = false; }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	};
}
// Compare this snippet from lve_device.hpp: