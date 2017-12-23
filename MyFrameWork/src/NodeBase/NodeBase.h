#pragma once

#include <forward_list>
#include <functional>

#include"NodePtr.h"

using NodeList = std::forward_list<NodeSPtr>;
class NodeBase
{	
public:
	NodeBase();
	~NodeBase();	
	//�A�b�v�f�[�g�i���g�A�q���j
	void Update();

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
	void RemoveChildren();
	//�q�������폜����
	void ClearChildren();
	//�q�̌���
	NodeSPtr FindNode(std::function<bool(const NodeBase&)>fn);
	//NodeList FindNodes(std::function<bool(const NodeBase&)>fn);

protected:
	virtual void OnUpdate() {}
private:
	NodeList mChildren;
	bool mIsDead;
};