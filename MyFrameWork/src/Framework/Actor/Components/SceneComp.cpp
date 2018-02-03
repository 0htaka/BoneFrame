//#include "SceneComp.h"
//
//SceneComp::SceneComp()
//{
//}
//
//SceneComp::~SceneComp()
//{
//}
//
//void SceneComp::UpdateWorldTransform()
//{
//
//}
//
//Vector3 SceneComp::GetRelativePos() const
//{
//	return m_RelativePos;
//}
//
//void SceneComp::SetRelativePos(const Vector3 & pos)
//{
//	m_RelativePos = pos;
//}
//
//Quaternion SceneComp::GetRelativeRot() const
//{
//	return m_RelativeRot;
//}
//
//void SceneComp::SetRelativeRot(const Quaternion& rot)
//{
//	m_RelativeRot = rot;
//}
//
//Vector3 SceneComp::GetRelativeScale() const
//{
//	return m_RelativeScale;
//}
//
//void SceneComp::SetRelativeScale(const Vector3 & scale)
//{
//	m_RelativeScale = scale;
//}
//
//Vector3 SceneComp::GetWorldPos() const
//{
//	return m_Parent->GetWorldPos() + m_RelativePos;
//}
//
//void SceneComp::SetWorldPos(const Vector3 & pos)
//{
//	m_RelativePos = pos - GetWorldPos();
//}
//
//Quaternion SceneComp::GetWorldRot() const
//{
//	return m_Parent->GetWorldRot() + m_RelativeRot;
//}
//
//void SceneComp::SetWorldRot(const Quaternion & rot)
//{
//	m_RelativeRot = rot - m_Parent->GetWorldRot();
//}
//
//Vector3 SceneComp::GetWorldScale() const
//{
//	const Vector3&& s1 = m_Parent->GetWorldScale();
//	const Vector3& s2 = m_RelativeScale;
//	return Vector3(s1.x * s2.x, s1.y * s2.y, s1.z * s2.z);
//}
//
//void SceneComp::SetWorldScale(const Vector3 & scale)
//{
//	
//}
