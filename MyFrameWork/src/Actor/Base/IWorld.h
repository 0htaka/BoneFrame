#ifndef	_IWORLD_H_
#define	_IWORLD_H_


#include<string>
enum class ActorGroup;
enum class EventMessage;
#include "ActorPtr.h"

#include"Camera\Camera.h"

//ワールド抽象インターフェース
class IWorld
{
public:
	//仮想デストラクタ
	virtual ~IWorld(){}
	//アクターの追加
	virtual void AddActor(const ActorSPtr& actor) = 0;	
	//アクターの検索
	virtual ActorSPtr FindActor(const std::string& name) = 0;
	
	//メッセージの送信
	virtual void Message(EventMessage message, void* param = nullptr) = 0;
	
	//virtual std::vector<ActorSPtr> FindActors(const ActorGroup& group) = 0;

	//virtual void AddField(std::shared_ptr<Field> field) = 0;
	//virtual std::shared_ptr<Field> GetField() const = 0;
	//virtual std::shared_ptr<Camera> GetCamera() const = 0;
	//virtual std::shared_ptr<SpriteManager> GetSpriteManager() const = 0;
};

#endif