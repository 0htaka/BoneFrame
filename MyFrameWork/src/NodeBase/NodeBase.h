#pragma once

#include <forward_list>
#include <functional>

#include"NodePtr.h"

enum class EventMessage;

using NodeList = std::forward_list<NodeSPtr>;
class NodeBase
{	
public:
	NodeBase();
	virtual ~NodeBase() {}
	//�A�b�v�f�[�g�i���g�A�q���j
	void Update(float deltaTime);

	//�q�̒ǉ�
	void AddChild(const NodeSPtr& child);
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
	NodeSPtr FindNode(std::function<bool(const NodeBase&)>fn);
	//NodeList FindNodes(std::function<bool(const NodeBase&)>fn);

	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);

protected:
	virtual void OnUpdate(float deltaTime) {}
private:
	NodeList mChildren;
	bool mIsDead;
};