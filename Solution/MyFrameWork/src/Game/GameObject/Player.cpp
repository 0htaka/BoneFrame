#include "Player.h"

void Player::OnUpdate(float deltaTime) {
	mAnimTimer += deltaTime;
	if (mAnimTimer >= mAnimation.EndTime())
		mAnimTimer = 0.0f;
	mSkinnedMesh.caluclate(GetPose(), deltaTime);

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
