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
	//�A�N�^�[�̒ǉ�
	void AddActor(const ActorSPtr& actor);
	//�A�N�^�[�̌���
	ActorSPtr FindActor(const std::string& name);

	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;
private:
	std::forward_list<ActorSPtr> mActors;
};

#endif