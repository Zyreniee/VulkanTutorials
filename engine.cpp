#include "engine.h"
#include "instance.h"
#include "logging.h"
#include "device.h"
#include "validation_layers.cpp"
using namespace Engine;

GLFWwindow* window;

void make_instance() {
	VkSurfaceKHR c_style_surface;
	if (glfwCreateWindowSurface(instance, window, nullptr, &c_style_surface) != VK_SUCCESS) {
		if (debugCallback) {
			std::cout << "Failed to abstract the glfw surface for vulkan" << std::endl;
		}
	
	}
}