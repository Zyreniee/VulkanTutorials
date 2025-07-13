#include "lve_window.hpp"
#include <string>
using namespace std;

namespace lve {
	lveWindow::lveWindow(int w, int h, string name) : width{ w }, height{ h }, windowName{ name } {
		InitWindow();
	}

	lveWindow::~lveWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	void lveWindow::InitWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
	
}//namespace lve