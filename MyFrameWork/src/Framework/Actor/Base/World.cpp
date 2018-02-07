#include "World.h"

void World::Update(float deltaTime) {
	mRoot.Update(deltaTime);

	mRoot.RemoveDead();
}

//アクターの追加
void World::AddActor(ActorPtr && actor) {
	mActors.AddActor({ actor.get() });
	mRoot.AddChild(std::move(actor));
}

RefPtr<Actor> World::FindActor(const std::string& name) {
	return mActors.FindActor(name);
}

//メッセージの送信

void World::Message(EventMessage message, void * param) {

}
