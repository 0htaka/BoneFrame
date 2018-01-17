#pragma once

#include"Design/Singleton.h"
#include<string>

template<typename Manager, typename Asset>
class IAssetManager : public Singleton<Manager> {
	virtual Asset& Get(const std::string& name) = 0;
	//virtual void Add(const Asset& asset) = 0;
	virtual void Remove(const std::string& name) = 0;
	virtual void Clear() = 0;
};