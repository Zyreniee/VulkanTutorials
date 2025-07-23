#include "lve_pipeline.hpp"
#include <vector>	
#include <iostream>
#include <string>
using namespace std;
//std
#include <fstream>
#include <stdexcept>
namespace Lve2 {

	//You should solve this problem tomorrow
	//Problem : Error in debug at this and lve_pipeline.hpp

}
namespace lve {

	LvePipeline::LvePipeline(
		const string& vertFilePath, const string& fragFilePath) {
		createGraphicsPipeline(vertFilePath, fragFilePath);
	}

	vector<char> LvePipeline::readFile(const string& filePath) {
		ifstream file{ filePath,ios::ate | ios::binary };
		size_t fileSize = static_cast<size_t>(file.tellg());
		vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}
	void LvePipeline::createGraphicsPipeline(
		const string& vertFilePath, const string& fragFilePath) {

		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		cout << "Vertex Shader Code Size: " << vertCode.size() << endl;
		cout << "Fragment Shader Code Size: " << fragCode.size() << endl;
	}
}//namespace lve
