#pragma once

#include "IWorld.h"
#include "Design/NodeBase/NodeBase.h"
#include "ActorManager.h"
#include "IWorld.h"

class World : public IWorld {
public:
	void Update(float deltaTime);
	//アクターの追加
	void AddActor(const ActorSPtr& actor) override;
	//アクターの検索
	ActorSPtr FindActor(const std::string& name) override;

	//メッセージの送信
	virtual void Message(EventMessage message, void* param = nullptr) override;
private:
	NodeBase mRoot;
	ActorManager mActors;
};