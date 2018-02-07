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
	// �J�n
	void start() override;
	// �X�V
	void update(float delta_time) override;
	// �`��
	void draw() override;
	// �I��
	void end() override;
private:
	bool m_isEnd{ false };
	SceneManager m_SceneManager;
	World mWorld;

	RefPtr<Camera> camera;
	RefPtr<Player> player;

	//**********************************************
	// �G�t�F�N�g
	EffectGL*		effect1_;
	EffectGL*		effect2_;

	SkinnedMeshShader* shader;

	// �A�j���[�V�����^�C�}
	float timer_ = 0.0f;
};