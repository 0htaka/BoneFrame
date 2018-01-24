#pragma once

#include"Scene\Base\SceneManager.h"

#include <Game/Frame.h>

#include "Render/EffectGL.h"
#include "Render/SkinnedMeshShader.h"
#include "Render/Mesh.h"
#include "Render/Skeleton.h"
#include "Render/Animation.h"
#include "Render/SkinnedMesh.h"

#include"Input\KeyInput\KeyInput.h"

#include"Actor\Player.h"
#include"Actor\Base\Camera\Camera.h"
#include"Actor/Base/World.h"

class MyGame : public boneLib::Frame {//gslib::Game {
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

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Player> player;

	//**********************************************
	// �G�t�F�N�g
	EffectGL*		effect1_;
	EffectGL*		effect2_;

	SkinnedMeshShader* shader;

	// �A�j���[�V�����^�C�}
	float timer_ = 0.0f;

};