#include "lve_window.hpp"
#include <stdexcept>
#include <iostream>

namespace lve
{
	// lveWindow sýnýfýnýn kurucusu: pencere boyutlarýný ve adýný ayarlar, pencereyi baþlatýr
	lveWindow::lveWindow(int w, int h, std::string name)
		: width{ w }, height{ h }, windowName{ name }
	{
		initWindow(); // Pencereyi baþlatan fonksiyon çaðrýlýr
	}

	// lveWindow sýnýfýnýn yýkýcýsý: pencereyi ve GLFW'u temizler
	lveWindow::~lveWindow()
	{
		glfwDestroyWindow(window); // Oluþturulan pencereyi yok et
		glfwTerminate(); // GLFW kütüphanesini sonlandýr
	}

	// GLFW kütüphanesi ile pencereyi baþlatan fonksiyon
	void lveWindow::initWindow()
	{
		glfwInit(); // GLFW baþlatýlýr
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // OpenGL veya baþka bir API kullanýlmayacak
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Pencere yeniden boyutlandýrýlamaz
		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr); // Pencere oluþturulur
		if (window == nullptr) {
			throw std::runtime_error("GLFW pencere oluþturulamadý!"); // Pencere oluþturulamazsa hata fýrlat
		}
	}
}