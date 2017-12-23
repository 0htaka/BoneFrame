#pragma once

#include"Base\Actor.h"
#include "Render/EffectGL.h"
#include "Render/SkinnedMeshShader.h"
#include "Render/Skeleton.h"
#include "Render/Animation.h"
#include "Render/SkinnedMesh.h"

class Player : public Actor
{
public:
	Player()
		: mSkinnedMesh{ mMesh, mSkeleton, mAnimation }
		, mAnimTime(0.0f)
	{
		mMesh.Load("asset/model/Soldier.mshs");
		mSkeleton.Load("asset/model/Soldier.skls");
		mAnimation.Load("asset/model/Y_Bot@jump.anms");
	}
	~Player() {
	}
	void OnUpdate(float deltaTime) override {
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
	void OnDraw() const override {
		mSkinnedMesh.draw(*mShader);
	}
	void TempDraw(Matrix world, Matrix view, Matrix projection, Light light) const {
		mShader->world(world);
		mShader->view(view);
		mShader->projection(projection);
		mShader->light(light);

		mSkinnedMesh.draw(*mShader);
	}
	void SetShader(SkinnedMeshShader* shader) {
		mShader = shader;
	}
private:
	// メッシュクラス
	Mesh			mMesh;
	// スケルトンクラス
	Skeleton		mSkeleton;
	// アニメーションクラス
	Animation		mAnimation;
	// スキニングメッシュクラス
	SkinnedMesh	mSkinnedMesh;
	//シェーダ
	SkinnedMeshShader* mShader;
	float mAnimTime;
};
