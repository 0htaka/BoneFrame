#include "NodeBase.h"
#include <algorithm>

NodeBase::NodeBase() : mIsDead(false) {}

void NodeBase::Update(float deltaTime) {
	OnUpdate(deltaTime);
	EachChildren([&deltaTime](NodeBase& actor) { actor.Update(deltaTime); });
}

void NodeBase::AddChild(NodePtr && child) {
	child->mParent = this;
	child->mId = mMaxChildId++;
	mChildren.push_front(std::move(child));
}

void NodeBase::EachChildren(std::function<void(NodeBase&)> fn) {
	std::for_each(mChildren.begin(), mChildren.end(),
		[&fn](const NodePtr& node) { fn(*node); });
}

void NodeBase::EachChildren(std::function<void(const NodeBase&)> fn) const {
	std::for_each(mChildren.cbegin(), mChildren.cend(),
		[&fn](const NodePtr& node) { fn(*node); });
}

void NodeBase::Kill() {
	mIsDead = true;
}

bool NodeBase::IsDead() {
	return mIsDead;
}

void NodeBase::RemoveChildren(std::function<bool(NodeBase&)> fn) {
	mChildren.remove_if([&fn](NodePtr& node) { return fn(*node); });
}

void NodeBase::RemoveDead() {
	RemoveChildren([](NodeBase& node) { return node.IsDead(); });
	EachChildren([](NodeBase& node) {node.RemoveDead(); });
}

void NodeBase::ClearChildren() {
	mChildren.clear();
}

NodeRPtr NodeBase::FindNode(std::function<bool(const NodeBase&)> fn) {
	auto& i = std::find_if(mChildren.begin(), mChildren.end(),
		[&fn](const NodePtr& child) { return fn(*child); });
	//�q	
	if (i != mChildren.end())
		return NodeRPtr((*i).get());

	//��
	for (auto& child : mChildren) {
		auto node = child->FindNode(fn);
		if (node != nullptr)
			return NodeRPtr(node);
	}
	return NodeRPtr(nullptr);
}

NodePtr NodeBase::RemoveChild(std::function<bool(NodePtr&)> fn) {
	auto& target = *(std::remove_if(mChildren.begin(), mChildren.end(), fn));
	target->mParent = nullptr;
	return std::move(target);
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

//���b�Z�[�W����
void NodeBase::HandleMessage(EventMessage message, void* param) {

}