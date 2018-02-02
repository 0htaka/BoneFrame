#pragma once

#include<string>

class ILoadable {
public:
	virtual void Load(const std::string& filePath) = 0;
	virtual void PrepareLoad(const std::string& filePath) {}
};