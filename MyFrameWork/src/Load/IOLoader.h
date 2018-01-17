#pragma once

#include <string>
#include <type.h>
#include <vector>

class IOLoader {
public:
	static std::vector<u_char> Load(const std::string& filePath);
	static std::string GetBaseName(const std::string& filePath);
	static std::string GetExtension(const std::string& filePath);
private:
	static std::size_t GerFileSize(std::ifstream& fs);
};