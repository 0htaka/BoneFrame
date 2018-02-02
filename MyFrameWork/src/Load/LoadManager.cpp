#include "LoadManager.h"
#include <GLFW/glfw3.h>
#include "Game/Window.h"
#include <fstream>
#include "IOLoader.h"

// �g�p����A�Z�b�g�}�l�[�W����
#include "AssetManager\MeshManager.h"
#include "AssetManager\AnimManager.h"
#include "AssetManager\SkeletonManager.h"

void LoadManager::Request(const std::string& filePath) {
	auto& manager = GetLoadablesManager(IOLoader::GetExtension(filePath));
	manager.PrepareLoad(filePath);
	mRequests.emplace(manager, filePath);
}

void LoadManager::LoadRequests() {
	GLFWwindow* subWin = bonelib::Window::createSubWin();
	if (!subWin)
		throw std::runtime_error("can't create sub window");

	////�񓯊�����
	std::thread t([&]() {
		glfwMakeContextCurrent(subWin);
		while (!mRequests.empty())
		{
			auto& item = mRequests.front();
			item.manager.Load(item.path);
			mRequests.pop();
		}
		//�쐬�����E�B���h�E�̍폜
		glfwMakeContextCurrent(nullptr);		
		//glfwDestroyWindow(subWin);

		//�����I����f�^�b�`
		mThread.detach();
	});
	mThread = std::move(t);
}

bool LoadManager::IsComplete() {
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
