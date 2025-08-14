#pragma once // Bu direktif, bu baþlýk dosyasýnýn (header) bir derleme sürecinde yalnýzca bir kez dahil edilmesini saðlar

#include <string> // std::string sýnýfýný kullanmak için gerekli
#include <vector> // std::vector sýnýfýný kullanmak için gerekli

namespace lve { // Kodun lve isim alaný (namespace) içinde tanýmlandýðýný belirtir
	class LvePipeline { // Vulkan pipeline’ýný temsil eden sýnýf
	public:
		// Constructor: Vertex ve fragment shader dosyalarýnýn yollarýný alarak bir pipeline nesnesi oluþturur
		LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath);

	private:
		// Belirtilen dosya yolunu okuyup byte’larý bir char vektöründe döndüren yardýmcý fonksiyon
		static std::vector <char> readFile(const std::string& filepath);

		// Grafik pipeline’ýný oluþturmak için kullanýlan fonksiyon
		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	};
}
