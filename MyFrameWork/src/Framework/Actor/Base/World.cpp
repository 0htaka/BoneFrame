#include "World.h"

void World::Update(float deltaTime)
{
	mRoot.Update(deltaTime);

	mRoot.RemoveDead();
}

//�A�N�^�[�̒ǉ�
void World::AddActor(const ActorSPtr & actor) {
	mActors.AddActor(actor);
	mRoot.AddChild(actor);
}

ActorSPtr World::FindActor(const std::string& name)
{
	return mActors.FindActor(name);
}

//���b�Z�[�W�̑��M

void World::Message(EventMessage message, void * param) {

}
