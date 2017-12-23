#pragma once

#include"Design/Singleton.h"
#include"ILoadable.h"
#include <unordered_map>
#include <filesystem>
#include <string>
#include <mutex>

template<typename Manager, typename Asset>
class AssetManagerBase : public Singleton<Manager> , public ILoadable {
public:
	void Load(const std::string& filePath) override {
		std::lock_guard<std::mutex> lock(mMutex);		
		OnLoad(filePath);
	}
	Asset& Get(const std::string& name) {
		std::lock_guard<std::mutex> lock(mMutex);
		return mAssets[name];
	}
	void Remove(const std::string& name) {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.erase(name);
	}
	void Clear() {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.clear();
	}

	std::string GetFileName(std::string filePath) {
		std::tr2::sys::path path(filePath);
		std::string fileNmae(path.filename().string());
		return fileNmae.erase(fileNmae.find_last_of('.'));
	}
protected:
	virtual void OnLoad(const std::string& filePath) {
		Asset asset;
		asset.Load(filePath);
		mAssets.emplace(GetFileName(filePath), std::move(asset));
	}
protected:
	std::unordered_map<std::string, Asset> mAssets;
	std::mutex mMutex;
};