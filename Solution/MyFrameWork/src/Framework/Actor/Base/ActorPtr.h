#ifndef _ACTOR_PTR_H_
#define _ACTOR_PTR_H_

#include "Design/NodeBase/NodePtr.h"
//�A�N�^�[�p�̃V�F�A�h�|�C���^
class Actor;
using ActorPtr = BonePtr<Actor>;
using ActorWPtr = std::weak_ptr<Actor>;


#endif