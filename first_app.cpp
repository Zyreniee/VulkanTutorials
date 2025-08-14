#include "first_app.hpp"
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
}