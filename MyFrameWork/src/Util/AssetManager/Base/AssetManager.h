#pragma once

#include"IAssetManager.h"

template<typename Asset>
class AssetManager : public IAssetManager<AssetManager<Asset>, Asset> {
public:
	void Add(const std::string& name, AssetUPtr&& asset) override {
		mAssets.emplace(name, std::move(asset));
	}
	Asset& Get(const std::string& name) override {
		return *mAssets.at(name);
	}	
	void Remove(const std::string& name) override {
		mAssets.erase(name);
	}
	void Clear() override {
		mAssets.clear();
	}
};