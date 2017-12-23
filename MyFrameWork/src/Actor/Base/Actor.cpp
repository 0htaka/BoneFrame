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

//�X�V
void Actor::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	EachChildren([&](Actor& actor) {actor.Update(deltaTime); });
}

//�`��
void Actor::Draw() const
{
	OnDraw();
	EachChildren([&](const Actor& actor) {actor.Draw(); });
}

//�Փ˔���
void Actor::Collide(Actor& other)
{
	Vector3 contactPos;
	HitInfo hitInfo;
	if (IsCollide(other, hitInfo))
	{
		OnCollide(other, hitInfo);
		other.OnCollide(*this, hitInfo);
	}
	EachChildren([&](Actor& actor) {actor.Collide(other); });
}

//���S���Ă��邩?
bool Actor::IsDead() const
{
	return m_isDead;
}

//���S����
void Actor::Dead()
{
	m_isDead = true;
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
std::vector<ActorSPtr> Actor::GetChilds()
{
	std::vector<ActorSPtr> result;
	for (auto child : children_)
	{
		result.push_back(child);
	}
	return result;
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

//�q�̌���
ActorSPtr Actor::FindChildren(const std::string& name)
{
	return FindChildren(
		[&](const Actor& actor) {return actor.GetName() == name; });
}
//�q�̌���
ActorSPtr Actor::FindChildren(std::function<bool(const Actor&)>fn)
{
	auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorSPtr& child) {return fn(*child); });

	if (i != children_.end())
	{
		return *i;
	}
	for (auto child : children_)
	{
		auto actor = child->FindChildren(fn);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}

//�q���m�̏Փ˔���
void Actor::CollideChildren(Actor& other)
{
	EachChildren([&](Actor& my) {
		other.EachChildren([&](Actor& target) {
			my.Collide(target); });
	});
}

//�Z�퓯�m�̏Փ˔���
void Actor::CollideSibling()
{
	for (auto i = children_.begin(); i != children_.end(); ++i)
	{
		std::for_each(std::next(i), children_.end(),
			[&](const ActorSPtr& actor) {(*i)->Collide(*actor); });
	}
}

//�q�̒ǉ�
void Actor::AddChild(const ActorSPtr& child)
{
	children_.push_front(child);
}
//�q������
void Actor::EachChildren(std::function<void(Actor&)> fn)
{
	std::for_each(children_.begin(), children_.end(),
		[&](const ActorSPtr& actor) { fn(*actor); });
}
//�q������(const��)
void Actor::EachChildren(std::function<void(const Actor&)> fn) const
{
	std::for_each(children_.begin(), children_.end(),
		[&](const ActorSPtr& actor) { fn(*actor); });
}

//�q���폜����
void Actor::RemoveChildren(std::function<bool(Actor& actor)>fn)
{
	children_.remove_if([&](ActorSPtr& actor) {return fn(*actor); });
}
//�q���폜����
void Actor::RemoveChildren()
{
	RemoveChildren([](Actor& actor) {return actor.IsDead(); });
	EachChildren([](Actor& actor) {actor.RemoveChildren(); });
}
//�q�������폜����
void Actor::ClearChildren()
{
	children_.clear();
}
//���b�Z�[�W����
void Actor::HandleMessage(EventMessage message, void* param)
{
	OnMessage(message, param);
	EachChildren([&](Actor& child) {child.HandleMessage(message, param); });
}

//���b�Z�[�W����
void Actor::OnMessage(EventMessage message, void* param)
{
	(void)message;
	(void)param;
}

//�X�V
void Actor::OnUpdate(float deltaTime)
{
	(void)deltaTime;
}

//�`��
void Actor::OnDraw() const
{
	//body_.translate(m_position).draw();//�f�o�b�O�\��
}

//�Փ˂���
void Actor::OnCollide(Actor& other, const HitInfo& info)
{
	(void)other;
	Dead();
}

void Actor::Translate(const Vector3 & vec)
{
	m_position += vec;
}

//�Փ˔���
bool Actor::IsCollide(const Actor& other, HitInfo& info)const
{
	return false;
}