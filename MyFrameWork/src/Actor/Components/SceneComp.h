#pragma once

#include"ComponentBase.h"
#include"SceneCompPtr.h"

#include"Math\Transform.h"
#include"Math\Matrix.h"

class SceneComp : public ComponentBase {
public:
	SceneComp();
	virtual ~SceneComp();	
	void AttachTo(SceneComp comp);
	void UpdateToWorldMatrix();

	/*******	get, set	*********/

	Vector3 GetRelativePos() const;
	void SetRelativePos(const Vector3& pos);
	Quaternion GetRelativeRot() const;
	void SetRelativeRot(const Quaternion& rot);
	Vector3 GetRelativeScale() const;
	void SetRelativeScale(const Vector3& scale);

	//未実装
	Vector3 GetWorldPos() const;
	void SetWorldPos(const Vector3& pos);
	Quaternion GetWorldRot() const;
	void SetWorldRot(const Quaternion& rot);
	Vector3 GetWorldScale() const;
	void SetWorldScale(const Vector3& scale);
protected:
	Transform m_RelativeTrans;

	Vector3 m_Velocity;

	//親コンポーネントとの連結
	std::weak_ptr<SceneComp> m_Parent;
	Matrix ToWorldTransform;
};