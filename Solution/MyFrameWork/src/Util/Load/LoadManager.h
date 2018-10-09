#pragma once

#include "Design/Singleton.h"
#include<queue>
#include<thread>
#include"ILoadable.h"

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
	//�񓯊��ǂݍ��݃L���[�ɒǉ�
	void Request(const std::string& filePath);
	//�L���[����񓯊��ǂݍ���
	void LoadRequests();
	//�H���[�h����
	bool IsComplete();

private:
	ILoadable& GetLoadablesManager(const std::string& extension);
private:
	std::queue<Item> _requests;
	std::thread _thread;
};