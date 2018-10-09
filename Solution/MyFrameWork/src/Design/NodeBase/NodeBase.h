#pragma once

#include <forward_list>
#include <functional>

#include "NodePtr.h"

enum class EventMessage;

using NodeList = std::forward_list<NodePtr>;
class NodeBase
{
	using IDType = unsigned int;
public:
	//�q�̍쐬
	template<typename T, typename ...TArgs>
	static BonePtr<T>& Make(TArgs&&... args);
public:
	NodeBase();
	virtual ~NodeBase() {}
	//�A�b�v�f�[�g�i���g�A�q���j
	void Update(float deltaTime);
	//�q�̒ǉ�
	void AddChild(NodePtr&& child);
	//�q������
	void EachChildren(std::function<void(NodeBase&)> fn);
	//�q������(const��)
	void EachChildren(std::function<void(const NodeBase&)> fn) const;
	//�m�[�h�폜
	void Kill();
	//���S�m�F
	bool IsDead();
	//�q���폜����
	void RemoveChildren(std::function<bool(NodeBase&)>fn);
	//�q���폜����
	void RemoveDead();
	//�q�������폜����
	void ClearChildren();
	//�q�̌���
	NodeRPtr FindNode(std::function<bool(const NodeBase&)>fn);
	//NodeList FindNodes(std::function<bool(const NodeBase&)>fn);

	NodePtr RemoveChild(std::function<bool(NodePtr&)> fn);	

	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
protected:
	virtual void OnUpdate(float deltaTime) {}
private:
	NodeRPtr mParent{ nullptr };
	IDType mId{ 0 };
	NodeList mChildren;
	IDType mMaxChildId{ 0 };
	bool mIsDead;
};

template<typename T, typename ...TArgs>
inline BonePtr<T> & NodeBase::Make(TArgs && ...args) {
	return std::make_shared<T>(std::forward<TArgs>(args)...);
}
