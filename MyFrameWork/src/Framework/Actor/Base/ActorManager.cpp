#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager()
{

}
void ActorManager::AddActor(const ActorPtr & actor)
{
	mActors.push_front(actor);
}

//アクターの検索
ActorPtr& ActorManager::FindActor(const std::string& name)
{
	auto it = std::find_if(mActors.begin(), mActors.end(),[&name](ActorPtr& actor) {
		return actor->GetName() == name;
	});
	return *it;
}
