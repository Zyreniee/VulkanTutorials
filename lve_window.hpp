#pragma once
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_VULKAN
#include <string>

namespace lve
{
	// lveWindow sýnýfý, pencere oluþturma ve yönetme iþlemlerini kapsar

	class lveWindow
	{
	private:
		void initWindow(); // Pencereyi baþlatan fonksiyon
		GLFWwindow* window; // GLFW pencere nesnesi
	public:
		lveWindow(int w, int h, std::string name); // Kurucu fonksiyon
		~lveWindow(); // Yýkýcý fonksiyon
		const int width = 800; // Pencere geniþliði
		const int height = 600; // Pencere yüksekliði
		std::string windowName; // Pencere baþlýðý

		lveWindow(const lveWindow&) = delete; // Kopyalama iþlemi engellendi
		lveWindow& operator=(const lveWindow&) = delete; // Atama iþlemi engellendi

		bool shouldClose() { return glfwWindowShouldClose(window); } // Pencere kapanmalý mý kontrolü

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface); 

		// EKSÝK FONKSÝYON EKLENDÝ
		GLFWwindow* getGLFWwindow() const { return window; }
	};
}