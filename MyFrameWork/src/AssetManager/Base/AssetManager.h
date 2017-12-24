#pragma once

#include"IAssetManager.h"

template<typename Manager, typename Asset>
class AssetManager : public IAssetManager<Manager, Asset> {
public:
	Asset& Get(const std::string& name) override {
		return mAssets[name];
	}
	void Add(const std::string& name, const Asset&& asset) {
		mAssets.emplace(name, asset);
	}
	void Remove(const std::string& name) override {
		mAssets.erase(name);	
	}
	void Clear() override {
		mAssets.clear();
	}
protected:
	std::unordered_map<std::string, Asset> mAssets;
};