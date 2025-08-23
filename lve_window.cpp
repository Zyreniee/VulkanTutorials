#include "lve_window.hpp"
#include <stdexcept>

namespace lve {

    lveWindow::lveWindow(int w, int h, std::string name)
        : width{ w }, height{ h }, windowName{ name } {
        initWindow();
    }

    lveWindow::~lveWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void lveWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void lveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    // lve_window.cpp içinde
    void lve::lveWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto lveWindow = reinterpret_cast<lve::lveWindow*>(glfwGetWindowUserPointer(window));
        lveWindow->framebufferResized = true;
        lveWindow->width = width;
        lveWindow->height = height;
    }


} // namespace lve
// Compare this snippet from lve_window.cpp: