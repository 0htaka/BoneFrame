#pragma once

#include "Framework/Scene/Base/SceneManager.h"

#include "Framework/Frame.h"
#include "Framework/Actor/Base/World.h"

class Camera;
class Player;
class EffectGL;
class SkinnedMeshShader;

class MyGame : public bonelib::Frame {//gslib::Game {
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
	World mWorld;

	RefPtr<Camera> camera;
	RefPtr<Player> player;

	//**********************************************
	// エフェクト
	EffectGL*		effect1_;
	EffectGL*		effect2_;

	SkinnedMeshShader* shader;

	// アニメーションタイマ
	float timer_ = 0.0f;
};