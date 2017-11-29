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
	KeyInput mKeyboard;

	//**********************************************
	// �G�t�F�N�g
	EffectGL*		effect1_;
	EffectGL*		effect2_;
	// ���b�V���N���X
	Mesh			mesh_;
	// �X�P���g���N���X
	Skeleton		skeleton_;
	// �A�j���[�V�����N���X
	Animation		animation_;
	// �X�L�j���O���b�V���N���X
	SkinnedMesh*	skinnedMesh_;
	SkinnedMeshShader* shader;

	// �A�j���[�V�����^�C�}
	float timer_ = 0.0f;

};