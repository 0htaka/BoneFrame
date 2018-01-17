#pragma once

#include "IAssetManager.h"
#include "Load/ILoadable.h"
#include <unordered_map>
#include <filesystem>
#include <string>
#include <mutex>

template<typename Manager, typename Asset>
class LoadablesManager : public IAssetManager<Manager, Asset>, public ILoadable {
	using Super = IAssetManager<Manager, Asset>;
public:
	void Load(const std::string& filePath) override {
		std::lock_guard<std::mutex> lock(mMutex);
		OnLoad(filePath);
	}
	Asset& Get(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		return mAssets.at(name);
	}
	void Remove(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.erase(name);
	}
	void Clear() override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.clear();
	}

	std::string GetFileName(const std::string& filePath) const {
		std::tr2::sys::path path(filePath);
		std::string fileNmae(path.filename().string());
		return fileNmae.erase(fileNmae.find_last_of('.'));
	}
protected:
	virtual void OnLoad(const std::string& filePath) {
		mAssets.emplace(GetFileName(filePath), Asset(filePath));
	}
protected:
	std::unordered_map<std::string, Asset> mAssets;
	std::mutex mMutex;
};

