#include "lve_pipeline.hpp"

// std kütüphaneleri
#include <fstream>      // Dosya okuma/yazma için
#include <iostream>     // std::cout gibi konsol çýktýlarý için
#include <stdexcept>    // Hata fýrlatma (throw) için

namespace lve
{
	// Constructor: Vertex ve fragment shader dosyalarýný alýp pipeline oluþturur
	LvePipeline::LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
		createGraphicsPipeline(vertFilepath, fragFilepath);
	}

	// Dosyayý okuyup içeriðini char vektörü olarak döndüren statik fonksiyon
	std::vector<char> LvePipeline::readFile(const std::string& filepath) {
		// Dosyayý aç, baþtan sona oku, binary modda
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary };
		if (!file.is_open()) {
			// Dosya açýlamadýysa runtime_error fýrlat
			throw std::runtime_error("failed to open file: " + filepath);
		}

		// Dosya boyutunu öðrenmek için tellg kullan
		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize); // Dosya boyutu kadar buffer oluþtur

		file.seekg(0); // Dosyanýn baþýna dön
		file.read(buffer.data(), fileSize); // Dosya içeriðini buffer’a oku

		file.close(); // Dosyayý kapat
		return buffer; // Buffer’ý geri döndür
	}

	// Grafik pipeline oluþturma fonksiyonu
	void LvePipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
		// Shader kodlarýný oku
		auto vertCode = readFile(vertFilepath);
		auto fragCode = readFile(fragFilepath);

		// Shader kodlarýnýn boyutunu konsola yazdýr (debug amaçlý)
		std::cout << "Vertex shader code size: " << vertCode.size() << std::endl;
		std::cout << "Fragment shader code size: " << fragCode.size() << std::endl;

		// Burada shader modülleri ve graphics pipeline oluþturulacak
	}
}
