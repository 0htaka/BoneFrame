#include"MyGame.h"
#include <GSgame.h>

#include"Screen\Screen.h"
#include"FPS\Time.h"
#include"Input\Input.h"
#include"Scene\Base\SceneManager.h"

#include"Scene\TestScene.h"

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
	mesh_.load("asset/model/Soldier.mshs");
	skeleton_.load("asset/model/Soldier.skls");
	animation_.load("asset/model/Y_Bot@jump.anms");
	effect1_ = new EffectGL("asset/shader/skinned_mesh.vert", "asset/shader/skinned_mesh.frag");
	effect2_ = new EffectGL("asset/shader/skinned_mesh_normal.vert", "asset/shader/skinned_mesh_normal.frag");
	skinnedMesh_ = new SkinnedMesh(mesh_, skeleton_, animation_);
	shader = new SkinnedMeshShader(*effect1_);

	mPlayer.SetShader(shader);
	mChar.SetShader(shader);
	mCamera.SetPosition({ 0.0f,15.0f, 40.0f });
	mCamera.SetRotate(mCamera.GetRotate().Forward(mPlayer.GetPosition() + Vector3{ 0, 10, 0 } - mCamera.GetPosition()));
}

void MyGame::update(float deltaTime)
{
	//���Ԃ̍X�V
	Time::Update();
	//deltaTime = Time::DeltaTime();

	//�V�[���X�V
	m_SceneManager.Update(deltaTime);

	mPlayer.Update(deltaTime);
	mChar.Update(deltaTime * 1.5f);
	mCamera.Update(deltaTime);

	/*:::::::::::::::::::::::::::::::::::*/
	skinnedMesh_->caluclate(Matrix::Identity, timer_);
	timer_ = std::fmod(timer_ + deltaTime, animation_.endFrame());

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
	Matrix CameraMat = mCamera.GetPose();
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
	mPlayer.TempDraw(world, view, projection, light);
	mChar.TempDraw(world, view, projection, light);

	//�t���[���Œ�
	//Time::Wait();
}


void MyGame::end()
{
	m_SceneManager.Finalize();

	delete skinnedMesh_;
	delete effect1_;
	delete effect2_;
}