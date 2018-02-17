#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager() {

}
void ActorManager::AddActor(RefPtr<Actor> actor) {
	mActors.push_front(actor.get());
}

//アクターの検索
RefPtr<Actor> ActorManager::FindActor(const std::string& name) {
	auto it = std::find_if(mActors.begin(), mActors.end(), [&name](const RefPtr<Actor>& actor) {
		return actor->GetName() == name;
	});
	return *it;
}
