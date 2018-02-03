#pragma once

#include<forward_list>
#include"ComponentBasePtr.h"

class CompManager
{
public:
	CompManager() {}
	~CompManager() {}
	void Update(float deltaTime) {}

	//template<T>
	//CompPtr GetComp() const { return m_Comps[0]; }
protected:
	//std::forward_list<CompPtr> m_Comps;
};