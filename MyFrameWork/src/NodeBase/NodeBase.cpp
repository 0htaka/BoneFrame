#include "NodeBase.h"
#include <algorithm>

NodeBase::NodeBase()
{
}

NodeBase::~NodeBase()
{
}

void NodeBase::Update()
{

}

void NodeBase::AddChild(const NodeSPtr & child)
{
	mChildren.push_front(child);
}

void NodeBase::EachChildren(std::function<void(NodeBase&)> fn)
{
	std::for_each(mChildren.begin(), mChildren.end(),
		[&fn](const NodeSPtr& node) { fn(*node); });
}

void NodeBase::EachChildren(std::function<void(const NodeBase&)> fn) const
{
	std::for_each(mChildren.cbegin(), mChildren.cend(),
		[&](const NodeSPtr& node) { fn(*node); });
}

void NodeBase::Kill()
{
	mIsDead = true;
}

bool NodeBase::IsDead()
{
	return mIsDead;
}

void NodeBase::RemoveChildren(std::function<bool(NodeBase&)> fn)
{
	mChildren.remove_if([&](NodeSPtr& node) {return fn(*node); });
}

void NodeBase::RemoveChildren()
{
	RemoveChildren([](NodeBase& node) { return node.IsDead(); });
	EachChildren([](NodeBase& node) {node.RemoveChildren(); });
}

void NodeBase::ClearChildren()
{
	mChildren.clear();
}

NodeSPtr NodeBase::FindNode(std::function<bool(const NodeBase&)> fn)
{
	auto i = std::find_if(mChildren.begin(), mChildren.end(),
		[&](const NodeSPtr& child) { return fn(*child); });
	//Žq
	if (i != mChildren.end())
		return *i;

	//‘·
	for (auto child : mChildren) {
		auto node = child->FindNode(fn);
		if (node != nullptr)
			return node;
	}
	return nullptr;
}

//NodeList NodeBase::FindNodes(std::function<bool(const NodeBase&)> fn)
//{
//	NodeList list;
//	auto pushFn =
//		[&fn, &list](const NodeSPtr& child) { if (fn(*child)) list.push_front(child); };
//
//	std::for_each(mChildren.begin(), mChildren.end(),
//		[&](const NodeSPtr& child) {
//		std::for_each
//		pushFn(child);
//	});
//
//	return list;
//}
