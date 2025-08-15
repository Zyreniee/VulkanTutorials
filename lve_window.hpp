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
		void initWindow();
		GLFWwindow* window;

	public:
		lveWindow(int w, int h, std::string name);
		~lveWindow();
		const int width = 800;
		const int height = 600;
		std::string windowName;

		lveWindow(const lveWindow&) = delete;
		lveWindow& operator=(const lveWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	};
}
// Compare this snippet from lve_device.hpp: