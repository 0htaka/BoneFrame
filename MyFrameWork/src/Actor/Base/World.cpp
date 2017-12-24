#include "World.h"

void World::Update(float deltaTime)
{
	mRoot.Update(deltaTime);

	mRoot.RemoveDead();
}

//アクターの追加
void World::AddActor(const ActorSPtr & actor) {
	mActors.AddActor(actor);
	mRoot.AddChild(actor);
}

ActorSPtr World::FindActor(const std::string& name)
{
	return mActors.FindActor(name);
}

//メッセージの送信

void World::Message(EventMessage message, void * param) {

}
