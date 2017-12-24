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

//�A�N�^�[�N���X
class Actor : public NodeBase
{
public:
	//�R���X�g���N�^
	Actor(IWorld& world, const std::string& name, const Vector3& position);
	//�R���X�g���N�^
	Actor(const std::string name = "none");

	//�f�X�g���N�^
	virtual ~Actor() {};

	//���O��Ԃ�
	const std::string& GetName() const;

	//���W��Ԃ�
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;

	void SetPosition(Vector3 sPos);
	Matrix GetRotate() const;
	void SetRotate(Matrix rotate);

	//�ϊ��s���Ԃ�
	Matrix GetPose() const;

	virtual void Translate(const Vector3& vec);

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
public:
	//���[���h
	IWorld*			m_world;
	//���O
	std::string		m_name;
	//���W
	Vector3			m_position;
	//�ړ�����
	Vector3			m_velocity;
	//��]	
	Matrix			m_rotate;
	//���S�t���O
	bool			m_isDead;	
private:
	//�R���|�[�l���g�̊Ǘ���
	CompManager		m_comps;
};

#endif