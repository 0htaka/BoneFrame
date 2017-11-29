#pragma once

#include"ComponentBasePtr.h"
#include"../Base/ActorPtr.h"
#include"CompManager.h"

class ComponentBase {
public:
	ComponentBase();
	virtual ~ComponentBase();
	virtual void Update(float deltaTime);
	void AttachTo(ActorSPtr act);

	ActorSPtr GetOwner();
	CompPtr GetParent() const;
protected:
	ActorWPtr m_Owner;
	CompManager m_comps;
};
