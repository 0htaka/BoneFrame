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
}

void Camera::OnUpdate(float deltaTime)
{
	
}

bool Camera::IsView(const Vector3& position, const float& angle)
{	
	return false;
}

