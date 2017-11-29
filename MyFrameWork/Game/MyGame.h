#pragma once

#include"Scene\Base\SceneManager.h"

#include <GSgame.h>

#include "Render/EffectGL.h"
#include "Render/SkinnedMeshShader.h"
#include "Render/Mesh.h"
#include "Render/Skeleton.h"
#include "Render/Animation.h"
#include "Render/SkinnedMesh.h"

#include"Input\KeyInput\KeyInput.h"

class MyGame : public gslib::Game {
public:
	MyGame();
	// 開始
	void start() override;
	// 更新
	void update(float delta_time) override;
	// 描画
	void draw() override;
	// 終了
	void end() override;
private:	
	bool m_isEnd{ false };
	SceneManager m_SceneManager;
	KeyInput mKeyboard;

	//**********************************************
	// エフェクト
	EffectGL*		effect1_;
	EffectGL*		effect2_;
	// メッシュクラス
	Mesh			mesh_;
	// スケルトンクラス
	Skeleton		skeleton_;
	// アニメーションクラス
	Animation		animation_;
	// スキニングメッシュクラス
	SkinnedMesh*	skinnedMesh_;
	SkinnedMeshShader* shader;

	// アニメーションタイマ
	float timer_ = 0.0f;

};