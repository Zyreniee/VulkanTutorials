#include <iostream>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include "first_app.hpp"
#include <cstdlib>
#include <stdexcept> 

// Programýn giriþ noktasý
#include "lve_window.hpp"

int main() {
	lve::FirstApp app{}; // Uygulama nesnesi oluþturuluyor
	try {
		app.run(); // Uygulama baþlatýlýyor
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl; // Hata mesajý ekrana yazdýrýlýr
		return EXIT_FAILURE; // Hata durumunda program sonlandýrýlýr
	}
	return EXIT_SUCCESS; // Baþarýlý þekilde çýkýþ yapýlýr
}
