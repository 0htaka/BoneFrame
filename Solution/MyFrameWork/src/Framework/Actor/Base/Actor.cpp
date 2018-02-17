#include"Actor.h"

#include"IWorld.h"
#include<algorithm>

//�R���X�g���N�^
Actor::Actor(IWorld& world, const std::string& name, const Vector3& position) :
	m_world(&world),
	m_name(name),
	m_position(position),
	m_rotate(Matrix::Identity),
	m_isDead(false),
	m_velocity({ 0, 0, 0 })
{
}
//�R���X�g���N�^
Actor::Actor(const std::string name)
	:m_world(nullptr),
	m_name(name),
	m_position(Vector3(0.0f, 0.0f, 0.0f)),
	m_rotate(Matrix::Identity),
	m_isDead(false),
	m_velocity(Vector3(0, 0, 0))
{
}

//���O��Ԃ�
const std::string& Actor::GetName() const
{
	return m_name;
}

//���W��Ԃ�
Vector3 Actor::GetPosition() const
{
	return m_position;
}

Vector3 Actor::GetVelocity() const
{
	return m_velocity;
}

void Actor::SetPosition(Vector3 sPos)
{
	m_position = sPos;
}

Matrix Actor::GetRotate() const
{
	return m_rotate;
}

void Actor::SetRotate(Matrix rotate)
{
	m_rotate = rotate;
	m_rotate.NormalizeRotationMatrix();
}
//�ϊ��s���Ԃ�
Matrix Actor::GetPose() const
{
	Matrix result = m_rotate;
	return result * Matrix::CreateTranslation(m_position);
}

void Actor::Translate(const Vector3 & vec)
{
	m_position += vec;
}