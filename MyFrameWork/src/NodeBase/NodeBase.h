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
	//アップデート（自身、子供）
	void Update(float deltaTime);

	//子の追加
	void AddChild(const NodeSPtr& child);
	//子を巡回
	void EachChildren(std::function<void(NodeBase&)> fn);
	//子を巡回(const版)
	void EachChildren(std::function<void(const NodeBase&)> fn) const;
	//ノード削除
	void Kill();
	//死亡確認
	bool IsDead();
	//子を削除する
	void RemoveChildren(std::function<bool(NodeBase&)>fn);
	//子を削除する
	void RemoveDead();
	//子を強制削除する
	void ClearChildren();
	//子の検索
	NodeSPtr FindNode(std::function<bool(const NodeBase&)>fn);
	//NodeList FindNodes(std::function<bool(const NodeBase&)>fn);

	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);

protected:
	virtual void OnUpdate(float deltaTime) {}
private:
	NodeList mChildren;
	bool mIsDead;
};