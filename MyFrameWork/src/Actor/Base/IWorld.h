#ifndef	_IWORLD_H_
#define	_IWORLD_H_


#include<string>
enum class ActorGroup;
enum class EventMessage;
#include "ActorPtr.h"

#include"Camera\Camera.h"

//���[���h���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	//���z�f�X�g���N�^
	virtual ~IWorld(){}
	//�A�N�^�[�̒ǉ�
	virtual void AddActor(const ActorSPtr& actor) = 0;	
	//�A�N�^�[�̌���
	virtual ActorSPtr FindActor(const std::string& name) = 0;
	
	//���b�Z�[�W�̑��M
	virtual void Message(EventMessage message, void* param = nullptr) = 0;
	
	//virtual std::vector<ActorSPtr> FindActors(const ActorGroup& group) = 0;

	//virtual void AddField(std::shared_ptr<Field> field) = 0;
	//virtual std::shared_ptr<Field> GetField() const = 0;
	//virtual std::shared_ptr<Camera> GetCamera() const = 0;
	//virtual std::shared_ptr<SpriteManager> GetSpriteManager() const = 0;
};

#endif