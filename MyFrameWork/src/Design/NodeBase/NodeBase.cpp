#include "NodeBase.h"
#include <algorithm>

NodeBase::NodeBase() : mIsDead(false)
{
}

void NodeBase::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	EachChildren([&](NodeBase& actor) {actor.Update(deltaTime); });
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

void NodeBase::RemoveDead()
{
	RemoveChildren([](NodeBase& node) { return node.IsDead(); });
	EachChildren([](NodeBase& node) {node.RemoveDead(); });
}

void NodeBase::ClearChildren()
{
	mChildren.clear();
}

NodeSPtr NodeBase::FindNode(std::function<bool(const NodeBase&)> fn)
{
	auto i = std::find_if(mChildren.begin(), mChildren.end(),
		[&](const NodeSPtr& child) { return fn(*child); });
	//子
	if (i != mChildren.end())
		return *i;

	//孫
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

//メッセージ処理
void NodeBase::HandleMessage(EventMessage message, void* param)
{

}