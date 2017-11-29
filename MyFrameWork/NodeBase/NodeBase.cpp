#include "NodeBase.h"

NodeBase::NodeBase()
{
}

NodeBase::~NodeBase()
{
}

void NodeBase::Update()
{
	for (auto child : m_Childs) {
		child.Update();
	}
}

bool NodeBase::IsDead()
{
	return m_IsDead;
}
