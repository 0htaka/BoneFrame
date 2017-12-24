#include "Player.h"

void Player::OnUpdate(float deltaTime) {
	mAnimTime += deltaTime;
	if (mAnimTime >= mAnimation.EndFrame())
		mAnimTime = 0.0f;
	mSkinnedMesh.caluclate(GetPose(), mAnimTime);

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
	m_position += velocity;
}
