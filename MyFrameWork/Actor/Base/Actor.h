#ifndef _ACTOR_H_
#define _ACTOR_H_

//#include<dxlib.h>

#include<string>
#include<functional>
#include<forward_list>
#include<vector>
#include<map>
#include "ActorPtr.h"
#include"Input\Input.h"
#include"Math\Vector3.h"
#include"Math\Matrix.h"

#include"../Components/CompManager.h"

class IWorld;
enum class EventMessage;

//アクタークラス
class Actor
{
public:
	//コンストラクタ
	Actor(IWorld& world, const std::string& name, const Vector3& position);
	//コンストラクタ
	Actor(const std::string name = "none");

	//デストラクタ
	virtual ~Actor() {};

	//更新
	void Update(float deltaTime);

	//描画
	void Draw() const;

	//衝突判定
	void Collide(Actor& other);

	//死亡しているか?
	bool IsDead() const;

	//死亡する
	void Dead();

	//名前を返す
	const std::string& GetName() const;

	//座標を返す
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;

	void SetPosition(Vector3 sPos);
	Matrix GetRotate() const;
	void SetRotate(Matrix rotate);

	//変換行列を返す
	Matrix GetPose() const;

	//子の検索
	ActorSPtr FindChildren(const std::string& name);
	//子の検索
	ActorSPtr FindChildren(std::function<bool(const Actor&)>fn);

	//子同士の衝突判定
	void CollideChildren(Actor& other);
	//兄弟同士の衝突判定
	void CollideSibling();

	//子の追加
	void AddChild(const ActorSPtr& child);
	//子を巡回
	void EachChildren(std::function<void(Actor&)> fn);
	//子を巡回(const版)
	void EachChildren(std::function<void(const Actor&)> fn) const;

	//子を削除する
	void RemoveChildren(std::function<bool(Actor& actor)>fn);
	//子を削除する
	void RemoveChildren();
	//子を強制削除する
	void ClearChildren();
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);	

	virtual void Translate(const Vector3& vec);
	//全ての子の取得
	std::vector<ActorSPtr> GetChilds();	

	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
private:
	//メッセージ処理
	virtual void OnMessage(EventMessage message, void* param);
	//更新
	virtual void OnUpdate(float deltaTime);
	//描画
	virtual void OnDraw() const;
	//衝突した
	virtual void OnCollide(Actor& other, const HitInfo& info);

	//衝突判定 それぞれ当たり判定が異なるので 押し出し処理があるので引数追加
	virtual bool IsCollide(const Actor& other, HitInfo& info)const;
protected:
	//ワールド
	IWorld*			m_world;
	//名前
	std::string		m_name;
	//座標
	Vector3			m_position;
	//移動方向
	Vector3			m_velocity;
	//回転	
	Matrix			m_rotate;
	//死亡フラグ
	bool			m_isDead;	
private:
	//子アクター
	std::forward_list<ActorSPtr> children_;
	//コンポーネントの管理を
	CompManager		m_comps;
};

#endif