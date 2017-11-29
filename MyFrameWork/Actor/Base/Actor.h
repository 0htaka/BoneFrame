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

//�A�N�^�[�N���X
class Actor
{
public:
	//�R���X�g���N�^
	Actor(IWorld& world, const std::string& name, const Vector3& position);
	//�R���X�g���N�^
	Actor(const std::string name = "none");

	//�f�X�g���N�^
	virtual ~Actor() {};

	//�X�V
	void Update(float deltaTime);

	//�`��
	void Draw() const;

	//�Փ˔���
	void Collide(Actor& other);

	//���S���Ă��邩?
	bool IsDead() const;

	//���S����
	void Dead();

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

	//�q�̌���
	ActorSPtr FindChildren(const std::string& name);
	//�q�̌���
	ActorSPtr FindChildren(std::function<bool(const Actor&)>fn);

	//�q���m�̏Փ˔���
	void CollideChildren(Actor& other);
	//�Z�퓯�m�̏Փ˔���
	void CollideSibling();

	//�q�̒ǉ�
	void AddChild(const ActorSPtr& child);
	//�q������
	void EachChildren(std::function<void(Actor&)> fn);
	//�q������(const��)
	void EachChildren(std::function<void(const Actor&)> fn) const;

	//�q���폜����
	void RemoveChildren(std::function<bool(Actor& actor)>fn);
	//�q���폜����
	void RemoveChildren();
	//�q�������폜����
	void ClearChildren();
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);	

	virtual void Translate(const Vector3& vec);
	//�S�Ă̎q�̎擾
	std::vector<ActorSPtr> GetChilds();	

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
private:
	//���b�Z�[�W����
	virtual void OnMessage(EventMessage message, void* param);
	//�X�V
	virtual void OnUpdate(float deltaTime);
	//�`��
	virtual void OnDraw() const;
	//�Փ˂���
	virtual void OnCollide(Actor& other, const HitInfo& info);

	//�Փ˔��� ���ꂼ�ꓖ���蔻�肪�قȂ�̂� �����o������������̂ň����ǉ�
	virtual bool IsCollide(const Actor& other, HitInfo& info)const;
protected:
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
	//�q�A�N�^�[
	std::forward_list<ActorSPtr> children_;
	//�R���|�[�l���g�̊Ǘ���
	CompManager		m_comps;
};

#endif