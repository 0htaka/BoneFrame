#pragma once

#include <forward_list>
#include <functional>

#include "NodePtr.h"

enum class EventMessage;

using NodeList = std::forward_list<NodePtr>;
class NodeBase
{
public:
	//子の作成
	template<typename T, typename ...Args>
	static BonePtr<T>& Make(Args&&... args);
public:
	NodeBase();
	virtual ~NodeBase() {}
	//アップデート（自身、子供）
	void Update(float deltaTime);
	//子の追加
	void AddChild(const NodePtr& child);
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
	NodePtr FindNode(std::function<bool(const NodeBase&)>fn);
	//NodeList FindNodes(std::function<bool(const NodeBase&)>fn);

	NodePtr RemoveChild(std::function<bool(NodePtr&)> fn);

	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
protected:
	virtual void OnUpdate(float deltaTime) {}
private:
	NodeRPtr mParent{ nullptr };
	NodeList mChildren;
	bool mIsDead;
};

template<typename T, typename ...Args>
inline BonePtr<T> & NodeBase::Make(Args && ...args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}
