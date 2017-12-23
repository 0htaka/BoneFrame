#include"MyGame.h"
#include <GSgame.h>

#include"Screen\Screen.h"
#include"FPS\Time.h"
#include"Input\Input.h"
#include"Scene\Base\SceneManager.h"

#include"Scene\TestScene.h"

#include"AssetManager/MeshManager.h"
#include"AssetManager/AnimManager.h"
#include"AssetManager/SkeletonManager.h"

#include"AssetManager/Base/LoadManager.h"

MyGame::MyGame()
	: gslib::Game()
	, m_isEnd(false)
{
}

void MyGame::start()
{
	//各ライブラリ、クラス等の初期化	

	//ロード等、頻繁に使うリソースのロード

	//シーンの追加
	m_SceneManager.Add(Scenes::GamePlay, std::make_shared<TestScene>());

	//最初のシーンを設定	
	m_SceneManager.Change(Scenes::GamePlay);

	// deltaTime を管理するクラスの初期化
	Time::Init();

	/*:::::::::::::::::::::::::::::::::::::::::::::*/
	/*MeshManager::Ins().Load("asset/model/Soldier.mshs");
	AnimManager::Ins().Load("asset/model/Y_Bot@jump.anms");
	SkeletonManager::Ins().Load("asset/model/Soldier.skls");*/
	LoadManager::Ins().Request("asset/model/Soldier.mshs");
	LoadManager::Ins().Request("asset/model/Y_Bot@jump.anms");
	LoadManager::Ins().Request("asset/model/Soldier.skls");	
	LoadManager::Ins().LoadRequests();

	/*while (true) {
		if (LoadManager::Ins().IsComplete())
			break;
	}*/

	mesh_ = &MeshManager::Ins().Get("Soldier");
	skeleton_ = &SkeletonManager::Ins().Get("Soldier");
	animation_ = &AnimManager::Ins().Get("Soldier");

	effect1_ = new EffectGL("asset/shader/skinned_mesh.vert", "asset/shader/skinned_mesh.frag");
	effect2_ = new EffectGL("asset/shader/skinned_mesh_normal.vert", "asset/shader/skinned_mesh_normal.frag");
	skinnedMesh_ = new SkinnedMesh(*mesh_, *skeleton_, *animation_);
	shader = new SkinnedMeshShader(*effect1_);

	mPlayer.SetShader(shader);
	mChar.SetShader(shader);
	mCamera.SetPosition({ 0.0f,15.0f, 40.0f });
	mCamera.SetRotate(mCamera.GetRotate().Forward(mPlayer.GetPosition() + Vector3{ 0, 10, 0 } -mCamera.GetPosition()));
}

void MyGame::update(float deltaTime)
{
	//時間の更新
	Time::Update();
	//deltaTime = Time::DeltaTime();

	//シーン更新
	m_SceneManager.Update(deltaTime);

	mPlayer.Update(deltaTime);
	mChar.Update(deltaTime * 1.5f);
	mCamera.Update(deltaTime);

	/*:::::::::::::::::::::::::::::::::::*/
	skinnedMesh_->caluclate(Matrix::Identity, timer_);
	timer_ = std::fmod(timer_ + deltaTime, animation_->EndFrame());

	Input::Ins().Update();
}

void MyGame::draw()
{
	//デバッグ用描画
	Time::Draw();

	//シーン描画
	m_SceneManager.Draw();

	/*:::::::::::::::::::::::::::::::::::::*/
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	Matrix world = Matrix::Identity;
	Matrix CameraMat = mCamera.GetPose();
	Matrix view = Matrix::CreateLookAt(CameraMat.Translation(), CameraMat.Translation() + CameraMat.Forward(), CameraMat.Up());
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(60.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	// ライトのパラメータ
	Light light;
	light.position = { 100.0f, 100.0f, 100.0f };

	EffectGL* effect = effect1_;

	shader->world(world);
	shader->view(view);
	shader->projection(projection);
	shader->light(light);

	//// メッシュの描画	
	mPlayer.TempDraw(world, view, projection, light);
	mChar.TempDraw(world, view, projection, light);

	//フレーム固定
	//Time::Wait();
}


void MyGame::end()
{
	m_SceneManager.Finalize();

	delete skinnedMesh_;
	delete effect1_;
	delete effect2_;
}