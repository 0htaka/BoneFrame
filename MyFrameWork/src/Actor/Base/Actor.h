#ifndef _ACTOR_H_
#define _ACTOR_H_

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

#include"NodeBase/NodeBase.h"

class IWorld;
enum class EventMessage;

//アクタークラス
class Actor : public NodeBase
{
public:
	//コンストラクタ
	Actor(IWorld& world, const std::string& name, const Vector3& position);
	//コンストラクタ
	Actor(const std::string name = "none");

	//デストラクタ
	virtual ~Actor() {};

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

	virtual void Translate(const Vector3& vec);

	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
public:
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
	//コンポーネントの管理を
	CompManager		m_comps;
};

#endif