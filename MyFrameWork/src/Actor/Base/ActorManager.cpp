#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager()
{

}
void ActorManager::AddActor(const ActorSPtr & actor)
{
	mActors.push_front(actor);
}

//アクターの検索
ActorSPtr ActorManager::FindActor(const std::string& name)
{
	auto it = std::find_if(mActors.begin(), mActors.end(),[&name](ActorSPtr& actor) {
		return actor->GetName() == name;
	});
	return *it;
}
