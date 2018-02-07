#pragma once

#include"NodeBase/NodeBase.h"
#include"ComponentBasePtr.h"
#include"../Base/ActorPtr.h"
#include"CompManager.h"

class ComponentBase : public NodeBase {
public:
	ComponentBase();
	virtual ~ComponentBase();
	virtual void Update(float deltaTime);
	void AttachTo(ActorPtr act);

	ActorPtr GetOwner();
	CompPtr GetParent() const;
protected:
	ActorWPtr m_Owner;
	CompManager m_comps;
};
