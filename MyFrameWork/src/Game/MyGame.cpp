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
	//各ライブラリ、クラス等の初期化	

	//ロード等、頻繁に使うリソースのロード

	//シーンの追加
	m_SceneManager.Add(Scenes::GamePlay, std::make_shared<TestScene>());

	//最初のシーンを設定	
	m_SceneManager.Change(Scenes::GamePlay);

	// deltaTime を管理するクラスの初期化
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
	//時間の更新
	Time::Update();
	//deltaTime = Time::DeltaTime();

	//シーン更新
	m_SceneManager.Update(deltaTime);

	mWorld.Update(deltaTime);

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
	Matrix CameraMat = camera->GetPose();
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
	player->TempDraw(world, view, projection, light);

	//フレーム固定
	//Time::Wait();
}


void MyGame::end()
{
	m_SceneManager.Finalize();

	delete effect1_;
	delete effect2_;
}