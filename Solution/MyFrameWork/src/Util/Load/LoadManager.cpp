#include "LoadManager.h"
#include <GLFW/glfw3.h>
#include "Util/Window/Window.h"
#include <fstream>
#include "IOLoader.h"

// 使用するアセットマネージャ一
#include "Util/AssetManager/MeshManager.h"
#include "Util/AssetManager/AnimManager.h"
#include "Util/AssetManager/SkeletonManager.h"
#include "Util/AssetManager/GLSLFragManager.h"
#include "Util/AssetManager/GLSLVertManager.h"

void LoadManager::Request(const std::string& filePath) {
	auto& manager = GetLoadablesManager(IOLoader::GetExtension(filePath));
	manager.PrepareLoad(filePath);
	_requests.emplace(manager, filePath);
}

void LoadManager::LoadRequests() {
	GLFWwindow* subWin = bonelib::Window::createSubWin();
	if (!subWin)
		throw std::runtime_error("can't create sub window");

	////非同期処理
	std::thread t([this, subWin]() {
		glfwMakeContextCurrent(subWin);
		while (!_requests.empty())
		{
			auto& item = _requests.front();
			item.manager.Load(item.path);
			_requests.pop();
		}
		//作成したウィンドウの削除
		glfwMakeContextCurrent(nullptr);
		//glfwDestroyWindow(subWin);

		//処理終了後デタッチ
		_thread.detach();
	});
	_thread = std::move(t);
}

bool LoadManager::IsComplete() {
	return !_thread.joinable();
}

ILoadable & LoadManager::GetLoadablesManager(const std::string& extension) {
	if (extension == ".mshs")
		return MeshManager::Ins();

	if (extension == ".anms")
		return AnimManager::Ins();

	if (extension == ".skls")
		return SkeletonManager::Ins();

	if (extension == ".vert")
		return GLSLVertManager::Ins();

	if (extension == ".frag")
		return GLSLFragManager::Ins();

	std::runtime_error("not found asset manager of " + extension);
	return MeshManager::Ins();
}
