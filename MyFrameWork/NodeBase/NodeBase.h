#pragma once

#include<vector>

class NodeBase
{
public:
	NodeBase();
	~NodeBase();
	void Update();
	bool IsDead();
protected:
	virtual void OnUpdate() {}
private:
	std::vector<NodeBase> m_Childs;
	bool m_IsDead;
};