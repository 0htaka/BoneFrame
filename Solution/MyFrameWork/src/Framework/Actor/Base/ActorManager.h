#ifndef	 _ACTOR_MANAGER_H_
#define	 _ACTOR_MANAGER_H_

#include<unordered_map>
#include"ActorPtr.h"
#include"Actor.h"

enum class ActorGroup;

//アクターマネージャー
class ActorManager
{
public:
	//コンストラクタ
	ActorManager();	
	//アクターの追加
	void AddActor(RefPtr<Actor> actor);
	//アクターの検索
	RefPtr<Actor> FindActor(const std::string& name);

	//コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;
private:
	std::forward_list<RefPtr<Actor>> mActors;
};

#endif