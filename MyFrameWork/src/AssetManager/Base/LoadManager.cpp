#include "LoadManager.h"
#include"AssetManager.h"

void LoadManager::Request(const std::string& filePath) {
	auto& manager = GetLoadablesManager(GetExtension(filePath));
	mRequests.emplace(manager, filePath);
}

void LoadManager::LoadRequests()
{
	std::thread t([this]() {
		while (!mRequests.empty())
		{
			auto& item = mRequests.back();
			item.manager.Load(item.path);
			mRequests.pop();
		}
		//処理終了後デタッチ
		mThread.detach();
	});
	mThread = std::move(t);
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

std::string LoadManager::GetExtension(const std::string & filePath)
{
	std::tr2::sys::path path(filePath);
	return path.extension().string();
}
