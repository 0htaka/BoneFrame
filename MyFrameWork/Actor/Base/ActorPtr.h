#ifndef _ACTOR_PTR_H_
#define _ACTOR_PTR_H_

#include<memory>
//アクター用のシェアドポインタ
class Actor;
using ActorSPtr = std::shared_ptr<Actor>;
using ActorWPtr = std::weak_ptr<Actor>;


#endif