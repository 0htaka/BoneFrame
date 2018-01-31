#pragma once

#include "IAssetManager.h"
#include "Load/ILoadable.h"
#include <filesystem>
#include <mutex>
#include <queue>

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
		return *mAssets.at(name);
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
	void CreateAsset() {
		mReqests.emplace(AssetUPtr(new Asset()));
	}
	AssetUPtr PopReqest() {
		AssetUPtr temp = std::move(mReqests.front());
		mReqests.pop();
		return temp;
	}
protected:
	virtual void OnLoad(const std::string& filePath) {
		//auto temp = std::make_unique<Asset>(filePath);
		auto& temp = PopReqest();
		temp->Load(filePath);
		auto fileName = GetFileName(filePath);
		mAssets.emplace(fileName, std::move(temp));
	}
protected:
	std::mutex mMutex;
	std::queue<AssetUPtr> mReqests;
};

//#include "Render\GLSLShader.h"
//class GLSLVertManager : public LoadablesManager<GLSLVertManager, GLSLShader> {
//protected:
//	virtual void OnLoad(const std::string& filePath) {
//		auto shader = std::make_unique<GLSLShader>(GL_VERTEX_SHADER, filePath);
//		mAssets.emplace(GetFileName(filePath), std::move(shader));
//	}
//};
//
//template<>
//void LoadablesManager<GLSLVertManager, std::unique_ptr<GLSLShader>>::OnLoad(const std::string& filePath) {
//	//std::make_unique<GLSLShader>(GL_VERTEX_SHADER, filePath);
//	//mAssets.emplace(GetFileName(filePath), );
//}
