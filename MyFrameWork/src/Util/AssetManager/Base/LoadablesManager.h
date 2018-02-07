#pragma once

#include "IAssetManager.h"
#include "Util/Load/ILoadable.h"
#include <filesystem>
#include <mutex>
#include <queue>

template<typename Manager, typename Asset>
class LoadablesManagerBase : public IAssetManager<Manager, Asset>, public ILoadable {
	using Super = IAssetManager<Manager, Asset>;
public:
	//アセットをロード、保持
	void Load(const std::string& filePath) override {
		auto fileName = GetFileName(filePath);
		auto& asset = OnLoad(filePath);
		Add(fileName, std::move(asset));
	}
	//アセットを追加
	void Add(const std::string& filePath, AssetUPtr&& asset) override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.emplace(filePath, std::move(asset));
	}
	//アセット取得
	Asset& Get(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		return *mAssets.at(name);
	}
	//アセットアンロード
	void Remove(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.erase(name);
	}
	//全てのアセットをアンロード
	void Clear() override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.clear();
	}

	//パスからファイル名を取得
	std::string GetFileName(const std::string& filePath) const {
		std::experimental::filesystem::path path(filePath);
		std::string fileNmae(path.filename().string());
		return fileNmae.erase(fileNmae.find_last_of('.'));
	}

	//ロード準備（メインスレッドで行っておくべきことを実行しておく）
	virtual void PrepareLoad(const std::string& filePath) {}

protected:
	//ロード時にアセットを加工する必要があればオーバーライド
	virtual AssetUPtr OnLoad(const std::string& filePath) = 0;
protected:
	std::mutex mMutex;
};

template<typename Manager, typename Asset>
class LoadablesManager : public LoadablesManagerBase<Manager, Asset> {
protected:
	//ロード時にアセットを加工する必要があればオーバーライド
	virtual AssetUPtr OnLoad(const std::string& filePath) {
		return std::make_unique<Asset>(filePath);
	}
};
