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
	//�A�Z�b�g�����[�h�A�ێ�
	void Load(const std::string& filePath) override {
		auto fileName = GetFileName(filePath);
		auto& asset = OnLoad(filePath);
		Add(fileName, std::move(asset));
	}
	//�A�Z�b�g��ǉ�
	void Add(const std::string& filePath, AssetUPtr&& asset) override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.emplace(filePath, std::move(asset));
	}
	//�A�Z�b�g�擾
	Asset& Get(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		return *mAssets.at(name);
	}
	//�A�Z�b�g�A�����[�h
	void Remove(const std::string& name) override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.erase(name);
	}
	//�S�ẴA�Z�b�g���A�����[�h
	void Clear() override {
		std::lock_guard<std::mutex> lock(mMutex);
		mAssets.clear();
	}

	//�p�X����t�@�C�������擾
	std::string GetFileName(const std::string& filePath) const {
		std::experimental::filesystem::path path(filePath);
		std::string fileNmae(path.filename().string());
		return fileNmae.erase(fileNmae.find_last_of('.'));
	}

	//���[�h�����i���C���X���b�h�ōs���Ă����ׂ����Ƃ����s���Ă����j
	virtual void PrepareLoad(const std::string& filePath) {}

protected:
	//���[�h���ɃA�Z�b�g�����H����K�v������΃I�[�o�[���C�h
	virtual AssetUPtr OnLoad(const std::string& filePath) = 0;
protected:
	std::mutex mMutex;
};

template<typename Manager, typename Asset>
class LoadablesManager : public LoadablesManagerBase<Manager, Asset> {
protected:
	//���[�h���ɃA�Z�b�g�����H����K�v������΃I�[�o�[���C�h
	virtual AssetUPtr OnLoad(const std::string& filePath) {
		return std::make_unique<Asset>(filePath);
	}
};
