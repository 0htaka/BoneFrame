#include "LoadManager.h"
#include <fstream>

#include "AssetManager\MeshManager.h"
#include "AssetManager\AnimManager.h"
#include "AssetManager\SkeletonManager.h"
#include "IOLoader.h"

void LoadManager::Request(const std::string& filePath) {
	auto& manager = GetLoadablesManager(IOLoader::GetExtension(filePath));
	mRequests.emplace(manager, filePath);
}

void LoadManager::LoadRequests()
{
	//std::thread t([this]() {
		while (!mRequests.empty())
		{
			auto& item = mRequests.front();
			item.manager.Load(item.path);
			mRequests.pop();
		}
	//	//処理終了後デタッチ
	//	mThread.detach();
	//});
	//mThread = std::move(t);
}

bool LoadManager::IsComplete()
{
	return !mThread.joinable();
}

ILoadable & LoadManager::GetLoadablesManager(const std::string& extension) {
	if (extension == ".mshs")
		return MeshManager::Ins();
	if (extension == ".anms")
		return AnimManager::Ins();
	if (extension == ".skls")
		return SkeletonManager::Ins();
	//if (extension == ".skls")
	//	return SkeletonManager::Ins();
}
