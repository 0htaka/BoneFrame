#pragma once

#include "Design/Singleton.h"
#include <string>
#include <unordered_map>
#include <memory>

template<typename SingletonType, typename Asset>
class IAssetManager : public Singleton<SingletonType> {	
protected:
	using AssetUPtr = std::unique_ptr<Asset>;
public:
	virtual void Add(const std::string& name, AssetUPtr&& asset) = 0;
	virtual Asset& Get(const std::string& name) = 0;
	virtual void Remove(const std::string& name) = 0;
	virtual void Clear() = 0;
protected:
	std::unordered_map<std::string, AssetUPtr> mAssets;
};