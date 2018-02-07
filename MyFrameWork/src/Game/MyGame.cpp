#include "MyGame.h"

#include "Util/Window/Screen/Screen.h"
#include "Util/Time.h"
#include "Util/Input/Input.h"
#include "Framework/Scene/Base/SceneManager.h"

#include "Framework/Scene/TestScene.h"

#include "Util/Load/LoadManager.h"
#include "Util/AssetManager/Base/AssetManager.h"
#include "Util/AssetManager/GLSLFragManager.h"
#include "Util/AssetManager/GLSLVertManager.h"

#include "Util/Render/EffectGL.h"
#include "Util/Render/SkinnedMeshShader.h"
#include "Util/Render/Mesh.h"
#include "Util/Render/Skeleton.h"
#include "Util/Render/Animation.h"
#include "Util/Render/SkinnedMesh.h"
#include "Framework/Actor/Camera/Camera.h"
#include "GameObject/Player.h"


//using EffectGLManager = AssetManager<EffectGL*>;
//class EffectGLManager : public AssetManager<EffectGL*> {};
#include"Util/RefPtr.h"
MyGame::MyGame()
	: bonelib::Frame()
	//: gslib::Game()
	, m_isEnd(false) {}

void MyGame::start() {
	//�e���C�u�����A�N���X���̏�����	

	//���[�h���A�p�ɂɎg�����\�[�X�̃��[�h

	//�V�[���̒ǉ�
	m_SceneManager.Add(Scenes::GamePlay, std::make_shared<TestScene>());

	//�ŏ��̃V�[����ݒ�	
	m_SceneManager.Change(Scenes::GamePlay);

	// deltaTime ���Ǘ�����N���X�̏�����
	Time::Init();

	/*:::::::::::::::::::::::::::::::::::::::::::::*/
	LoadManager::Ins().Request("asset/model/Soldier.mshs");
	LoadManager::Ins().Request("asset/model/FUCM_04_0001_RHiKick.anms");
	LoadManager::Ins().Request("asset/model/Soldier.skls");
	LoadManager::Ins().Request("asset/shader/skinned_mesh_normal.vert");
	LoadManager::Ins().Request("asset/shader/skinned_mesh_normal.frag");
	LoadManager::Ins().LoadRequests();

	while (!LoadManager::Ins().IsComplete());

	effect2_ = new EffectGL(GLSLVertManager::Ins().Get("skinned_mesh_normal"), GLSLFragManager::Ins().Get("skinned_mesh_normal"))
	shader = new SkinnedMeshShader(*effect2_);

	auto uPlayer = std::make_unique<Player>();
	auto uCamera = std::make_unique<Camera>();
	player = uPlayer.get();
	player->SetShader(shader);
	camera = uCamera.get();
	camera->SetPosition({ 0.0f,15.0f, 40.0f });

	mWorld.AddActor(std::move(uPlayer));
	mWorld.AddActor(std::move(uCamera));

	camera->SetRotate(camera->GetRotate().Forward(player->GetPosition() + Vector3{ 0, 10, 0 } -camera->GetPosition()));
}

void MyGame::update(float deltaTime) {
	//���Ԃ̍X�V
	Time::Update();
	//deltaTime = Time::DeltaTime();

	//�V�[���X�V
	m_SceneManager.Update(deltaTime);

	mWorld.Update(deltaTime);

	Input::Ins().Update();
}

void MyGame::draw() {
	//�f�o�b�O�p�`��
	Time::Draw();

	//�V�[���`��
	m_SceneManager.Draw();

	/*:::::::::::::::::::::::::::::::::::::*/
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	Matrix world = Matrix::Identity;
	Matrix CameraMat = camera->GetPose();
	Matrix view = Matrix::CreateLookAt(CameraMat.Translation(), CameraMat.Translation() + CameraMat.Forward(), CameraMat.Up());
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(60.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	// ���C�g�̃p�����[�^
	Light light;
	light.position = { 100.0f, 100.0f, 100.0f };

	EffectGL* effect = effect1_;

	shader->world(world);
	shader->view(view);
	shader->projection(projection);
	shader->light(light);

	//// ���b�V���̕`��
	player->TempDraw(world, view, projection, light);

	//�t���[���Œ�
	//Time::Wait();
}


void MyGame::end() {
	m_SceneManager.Finalize();

	delete effect1_;
	delete effect2_;
}