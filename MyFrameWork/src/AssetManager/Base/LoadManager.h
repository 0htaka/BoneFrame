#pragma once

#include<queue>
#include<string>
#include"ILoadable.h"

#include "../MeshManager.h"
#include "../AnimManager.h"
#include "../SkeletonManager.h"

class LoadManager : public Singleton<LoadManager> {
	struct Item
	{
		ILoadable& manager;
		std::string path;

		Item(ILoadable& manager, const std::string& path)
			: manager{ manager }
			, path{ path }
		{}
	};

public:
	//非同期読み込みにキューに追加
	void Request(const std::string& filePath);
	//キュー内を非同期読み込み
	void LoadRequests();
	//？ロード完了
	bool IsComplete();
private:
	ILoadable& GetLoadablesManager(const std::string& extension);
	std::string GetExtension(const std::string& filePath);
private:
	std::queue<Item> mRequests;
	std::thread mThread;
};