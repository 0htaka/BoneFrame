#pragma once

#include "Base/LoadablesManager.h"
#include "Util/Render/Mesh.h"
#include <string>

class MeshManager : public LoadablesManager<MeshManager, Mesh> {
private:
	void PrepareLoad(const std::string& filePath) override {
		mReqests.emplace(AssetUPtr(new Mesh()));
	}
protected:
	virtual AssetUPtr OnLoad(const std::string& filePath) override {
		AssetUPtr temp = std::move(mReqests.front());
		mReqests.pop();
		temp->Load(filePath);
		return std::move(temp);
	}
private:
	std::queue<AssetUPtr> mReqests;
};