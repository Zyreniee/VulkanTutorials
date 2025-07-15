#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace lve {
	class LvePipeline {
	public:
		LvePipeline(const string& vertFilePath, const string& fragFilePath);

	private:
		static vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(const string& vertFilePath, const string& fragFilePath);
	};
}//namespace lve