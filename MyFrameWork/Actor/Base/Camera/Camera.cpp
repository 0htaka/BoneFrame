#include"Camera.h"
#include"../IWorld.h"
#include"Math/Matrix.h"
#include<math.h>
#include"Input\Input.h"

#include"Screen\Screen.h"

const float VIEW_ANGLE = 45.0f;
const float LERP_TIME = 10.0f;

Camera::Camera()	
{
	SetPosition({ 0.0f, 10.0f, 20.0f });
}

void Camera::OnUpdate(float deltaTime)
{
	/*Matrix rot;
	Vector3 velocity;
	if (Input::Ins().mKeys.GetKeyState(VK_UP)) {
		velocity += m_rotate.Forward();
	}
	if (Input::Ins().mKeys.GetKeyState(VK_DOWN)) {
		velocity += m_rotate.Backward();
	}
	if (Input::Ins().mKeys.GetKeyState(VK_LEFT)) {
		velocity += m_rotate.Left();
	}
	if (Input::Ins().mKeys.GetKeyState(VK_RIGHT)) {
		velocity += m_rotate.Right();
	}
	m_rotate.Up(Vector3::Up);
	m_rotate.Forward(Vector3(0.0f,0.0f,0.0f) - m_position);	
	m_position += velocity;	*/
}
void Camera::OnDraw()const
{	
}

bool Camera::IsView(const Vector3& position, const float& angle)
{	
	return false;
}

void Camera::OnCollide(Actor & other, const HitInfo & info)
{

}
