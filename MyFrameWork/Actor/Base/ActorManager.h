#ifndef	 _ACTOR_MANAGER_H_
#define	 _ACTOR_MANAGER_H_

#include<unordered_map>
#include"ActorPtr.h"
#include"Actor.h"

enum class ActorGroup;

//�A�N�^�[�}�l�[�W���[
class ActorManager
{
public:
	//�R���X�g���N�^
	ActorManager();
	//������
	void Initialize();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//�A�N�^�[�̒ǉ�
	void AddActor(ActorGroup group, const ActorSPtr& actor);
	//�A�N�^�[�̌���
	ActorSPtr FindActor(const std::string& name);
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
	std::vector<ActorSPtr> FindActors(const ActorGroup& group);

	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;
private:
	//�Փ˔���
	void Collide();
private:
	//���[�g�m�[�h(Find��HandleMessage�Ɏg�p�j
	Actor m_root;

	//Draw���Ȃ�Actor�iBlock���j
	ActorSPtr m_updateActor;
	//Update���Ȃ�Actor�iManager���j
	ActorSPtr m_drawActor;
	//Update && Draw
	ActorSPtr m_bothActor;

	//�A�N�^�[�O���[�v
	std::unordered_map<ActorGroup, ActorSPtr> m_actors;

};

#endif