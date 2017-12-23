#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager()
	: m_bothActor(std::make_shared<Actor>())
	, m_updateActor(std::make_shared<Actor>())
	, m_drawActor(std::make_shared<Actor>())

{
	m_root.AddChild(m_updateActor);
	m_root.AddChild(m_drawActor);
	m_root.AddChild(m_bothActor);

	Initialize();
}
//初期化
void ActorManager::Initialize()
{
	m_actors[ActorGroup::Player] = std::make_shared<Actor>();
}

//更新
void ActorManager::Update(float deltaTime)
{
	m_bothActor->Update(deltaTime);
	m_updateActor->Update(deltaTime);

	Collide();
	m_root.RemoveChildren();
}

//描画
void ActorManager::Draw() const
{
	m_bothActor->Draw();
	m_drawActor->Draw();
}

void ActorManager::AddActor(ActorGroup group, const ActorSPtr & actor)
{
	m_actors[group]->AddChild(actor);
}

//アクターの検索
ActorSPtr ActorManager::FindActor(const std::string& name)
{
	return m_root.FindChildren(name);
}

//メッセージ処理
void ActorManager::HandleMessage(EventMessage message, void* param)
{
	m_root.HandleMessage(message, param);
}
std::vector<ActorSPtr> ActorManager::FindActors(const ActorGroup & group)
{
	return m_actors[group]->GetChilds();
}
//衝突判定
void ActorManager::Collide()
{

}

