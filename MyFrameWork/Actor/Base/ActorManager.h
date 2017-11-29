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
	//初期化
	void Initialize();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//アクターの追加
	void AddActor(ActorGroup group, const ActorSPtr& actor);
	//アクターの検索
	ActorSPtr FindActor(const std::string& name);
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
	std::vector<ActorSPtr> FindActors(const ActorGroup& group);

	//コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;
private:
	//衝突判定
	void Collide();
private:
	//ルートノード(FindとHandleMessageに使用）
	Actor m_root;

	//DrawしないActor（Block等）
	ActorSPtr m_updateActor;
	//UpdateしないActor（Manager等）
	ActorSPtr m_drawActor;
	//Update && Draw
	ActorSPtr m_bothActor;

	//アクターグループ
	std::unordered_map<ActorGroup, ActorSPtr> m_actors;

};

#endif