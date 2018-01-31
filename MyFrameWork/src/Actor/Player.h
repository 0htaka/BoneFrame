#pragma once

#include"Base\Actor.h"
#include "Render/EffectGL.h"
#include "Render/SkinnedMeshShader.h"
#include "Render/Skeleton.h"
#include "Render/Animation.h"
#include "Render/SkinnedMesh.h"
#include "AssetManager/MeshManager.h"

class Player : public Actor
{
public:
	Player()
		: mSkinnedMesh{ mMesh, mSkeleton, mAnimation }
		, mAnimTimer(0.0f)
		, mMesh{ MeshManager::Ins().Get("Soldier") }
	{
		//mMesh.Load("asset/model/Soldier.mshs");
		//Mesh mesh;
		//mesh.Load("asset/model/Soldier.mshs");
		mSkeleton.Load("asset/model/Soldier.skls");
		mAnimation.Load("asset/model/Y_Bot@jump.anms");
	}
	~Player() {
	}
	void OnUpdate(float deltaTime) override;
	void OnDraw() const {
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
	Mesh&			mMesh;
	// スケルトンクラス
	Skeleton		mSkeleton;
	// アニメーションクラス
	Animation		mAnimation;
	// スキニングメッシュクラス
	SkinnedMesh		mSkinnedMesh;
	//シェーダ
	SkinnedMeshShader* mShader;
	float mAnimTimer;
};
