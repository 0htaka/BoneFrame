#include "LoadManager.h"
#include <fstream>

#include "AssetManager\MeshManager.h"
#include "AssetManager\AnimManager.h"
#include "AssetManager\SkeletonManager.h"
#include "IOLoader.h"

void LoadManager::Request(const std::string& filePath) {
	auto& manager = GetLoadablesManager(IOLoader::GetExtension(filePath));
	manager.PrepareLoad(filePath);
	mRequests.emplace(manager, filePath);
}

#include "Game/Window.h"
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
void LoadManager::LoadRequests()
{
#define A
#ifdef MYSUBWIN
	//auto subWin = bonelib::Window::createSubWin();
	auto subWin = bonelib::Window::sSubWindow;
	if (!subWin)
		throw std::runtime_error("can't create sub window");

	////非同期処理
	std::thread t([&]() {
		glfwMakeContextCurrent(subWin);
		while (!mRequests.empty())
		{
			auto& item = mRequests.front();
			item.manager.Load(item.path);
			mRequests.pop();
		}
		glfwMakeContextCurrent(nullptr);
		//処理終了後デタッチ
		//mThread.detach();
	});
	//mThread = std::move(t);
	t.join();

#else
	//同期バージョン
	while (!mRequests.empty())
	{
		auto& item = mRequests.front();
		item.manager.Load(item.path);
		mRequests.pop();
	}

#endif // SUB	
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
