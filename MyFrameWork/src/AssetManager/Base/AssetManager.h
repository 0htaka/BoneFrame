#pragma once

#include"IAssetManager.h"

template<typename Asset>
class AssetManagerMap : public IAssetManager<AssetManagerMap<Asset>, Asset> {
public:
	Asset& Get(const std::string& name) override {
		return mAssets.at(name);
	}
	void Add(const std::string& name, Asset&& asset) {
		mAssets.emplace(name, std::forward(asset));
	}
	void Remove(const std::string& name) override {
		/*if (std::is_pointer<Asset>::value)
			delete mAssets.at(name);*/
		mAssets.erase(name);
	}
	void Clear() override {
		//if (std::is_pointer<Asset>::value) {
		//	for (auto p : mAssets) {
		//		delete p.second;
		//	}
		//}
		mAssets.clear();
	}	
protected:
	std::unordered_map<std::string, Asset> mAssets;
};
