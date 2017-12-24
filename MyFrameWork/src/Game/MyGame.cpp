#include"MyGame.h"
#include <GSgame.h>

#include"Screen\Screen.h"
#include"FPS\Time.h"
#include"Input\Input.h"
#include"Scene\Base\SceneManager.h"

#include"Scene\TestScene.h"

#include"AssetManager/Base/LoadManager.h"
#include"AssetManager\Base\AssetManager.h"

MyGame::MyGame()
	: gslib::Game()
	, m_isEnd(false)
{
}



void MyGame::start()
{
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
	LoadManager::Ins().Request("asset/model/Y_Bot@jump.anms");
	LoadManager::Ins().Request("asset/model/Soldier.skls");
	LoadManager::Ins().LoadRequests();

	while (true) {
		if (LoadManager::Ins().IsComplete())
			break;
	}

	effect1_ = new EffectGL("asset/shader/skinned_mesh.vert", "asset/shader/skinned_mesh.frag");
	effect2_ = new EffectGL("asset/shader/skinned_mesh_normal.vert", "asset/shader/skinned_mesh_normal.frag");
	shader = new SkinnedMeshShader(*effect2_);

	player = std::make_shared<Player>();
	player->SetShader(shader);
	camera = std::make_shared<Camera>();
	camera->SetPosition({ 0.0f,15.0f, 40.0f });

	mWorld.AddActor(player);
	mWorld.AddActor(camera);

	camera->SetRotate(camera->GetRotate().Forward(player->GetPosition() + Vector3{ 0, 10, 0 } -camera->GetPosition()));
}

void MyGame::update(float deltaTime)
{
	//���Ԃ̍X�V
	Time::Update();
	//deltaTime = Time::DeltaTime();

	//�V�[���X�V
	m_SceneManager.Update(deltaTime);

	mWorld.Update(deltaTime);

	Input::Ins().Update();
}

void MyGame::draw()
{
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


void MyGame::end()
{
	m_SceneManager.Finalize();

	delete effect1_;
	delete effect2_;
}