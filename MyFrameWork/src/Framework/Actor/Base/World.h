#pragma once

#include "IWorld.h"
#include "Design/NodeBase/NodeBase.h"
#include "ActorManager.h"
#include "IWorld.h"

class World : public IWorld {
public:
	void Update(float deltaTime);
	//�A�N�^�[�̒ǉ�
	void AddActor(const ActorSPtr& actor) override;
	//�A�N�^�[�̌���
	ActorSPtr FindActor(const std::string& name) override;

	//���b�Z�[�W�̑��M
	virtual void Message(EventMessage message, void* param = nullptr) override;
private:
	NodeBase mRoot;
	ActorManager mActors;
};