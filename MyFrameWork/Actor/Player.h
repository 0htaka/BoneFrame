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
		: mSkinnedMesh{ mMesh,mSkeleton,mAnimation }
		, mAnimTime(0.0f)
	{
		mMesh.load("asset/model/Soldier.mshs");
		mSkeleton.load("asset/model/Soldier.skls");
		mAnimation.load("asset/model/Y_Bot@jump.anms");
	}
	~Player() {
	}
	void OnUpdate(float deltaTime) override {
		mAnimTime += deltaTime;
		mSkinnedMesh.caluclate(GetPose(), mAnimTime);
	}
	void OnDraw() const override {
		mSkinnedMesh.draw(*mShader);
	}
private:
	// ���b�V���N���X
	Mesh			mMesh;
	// �X�P���g���N���X
	Skeleton		mSkeleton;
	// �A�j���[�V�����N���X
	Animation		mAnimation;
	// �X�L�j���O���b�V���N���X
	SkinnedMesh	mSkinnedMesh;
	//�V�F�[�_
	SkinnedMeshShader* mShader;
	float mAnimTime;
};
