#pragma once
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_VULKAN

#include <string>
using namespace std;
namespace lve {
	class lveWindow {
	public:
		lveWindow(int w, int h, string name);
	   ~lveWindow();

	   lveWindow(const lveWindow&) = delete;
	   lveWindow& operator=(const lveWindow&) = delete;
	   bool shouldClose() { return glfwWindowShouldClose(window); }
	private:
		void InitWindow();

		const int width;
		const int height;
		GLFWwindow *window;
		std::string windowName;
	};
}//namespace lve