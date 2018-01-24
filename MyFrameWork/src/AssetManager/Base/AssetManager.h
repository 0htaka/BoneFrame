#pragma once

#include"IAssetManager.h"

template<typename Asset>
class AssetManager : public IAssetManager<AssetManager<Asset>, Asset> {
public:
	Asset& Get(const std::string& name) override {
		return *mAssets.at(name);
	}
	void Add(const std::string& name, Asset&& asset) {
		auto assetUPtr = std::make_unique(new Asset(std::move(asset)));
		mAssets.emplace(name, asset);
	}
	void Remove(const std::string& name) override {
		mAssets.erase(name);
	}
	void Clear() override {
		mAssets.clear();
	}
};