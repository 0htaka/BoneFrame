#include "MyGame.h"

#include "Util/Window/Screen/Screen.h"
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

#include"Util/RefPtr.h"


MyGame::MyGame()
	: bonelib::Frame()
	, m_isEnd(false) {}
Player* ptest;
SkinnedMeshShader* stest;
void MyGame::start() {
	//各ライブラリ、クラス等の初期化	

	//ロード等、頻繁に使うリソースのロード

	//シーンの追加
	m_SceneManager.Add(Scenes::GamePlay, std::make_shared<TestScene>());

	//最初のシーンを設定	
	m_SceneManager.Change(Scenes::GamePlay);

	/*:::::::::::::::::::::::::::::::::::::::::::::*/
	LoadManager::Ins().Request("asset/model/Soldier.mshs");
	LoadManager::Ins().Request("asset/model/Monster3.mshs");
	LoadManager::Ins().Request("asset/model/FUCM_04_0001_RHiKick.anms");
	LoadManager::Ins().Request("asset/model/Soldier.skls");
	LoadManager::Ins().Request("asset/model/Monster3.skls");
	LoadManager::Ins().Request("asset/shader/skinned_mesh_normal.vert");
	LoadManager::Ins().Request("asset/shader/skinned_mesh_normal.frag");
	LoadManager::Ins().Request("asset/shader/test_skinmesh.frag");
	LoadManager::Ins().LoadRequests();

	while (!LoadManager::Ins().IsComplete());

	effect1_ = new EffectGL(GLSLVertManager::Ins().Get("skinned_mesh_normal"), GLSLFragManager::Ins().Get("skinned_mesh_normal"));
	effect2_ = new EffectGL(GLSLVertManager::Ins().Get("skinned_mesh_normal"), GLSLFragManager::Ins().Get("test_skinmesh"));
	shader = new SkinnedMeshShader(*effect1_);
	stest = new SkinnedMeshShader(*effect2_);

	std::unique_ptr<Player> temp(new Player());
	temp->SetShader(stest);
	temp->SetPosition({ 3, 0, 0 });
	ptest = temp.get();

	auto uPlayer = std::make_unique<Player>();
	auto uCamera = std::make_unique<Camera>();
	player = uPlayer.get();
	player->SetShader(shader);
	player->SetPosition({ 0,0,0 });
	camera = uCamera.get();
	camera->SetPosition({ 0.0f,15.0f, 40.0f });
	camera->SetRotate(camera->GetRotate().Forward(ptest->GetPosition() + Vector3{ 0, 10, 0 } -camera->GetPosition()));

	mWorld.AddActor(std::move(uPlayer));
	mWorld.AddActor(std::move(temp));
	mWorld.AddActor(std::move(uCamera));
}

void MyGame::update(float deltaTime) {
	//シーン更新
	m_SceneManager.Update(deltaTime);

	mWorld.Update(deltaTime);

	float temp = Time::DeltaSec();
}

void MyGame::draw() {
	//シーン描画
	m_SceneManager.Draw();
	//render_string(0, 0, Time::toString());

	/*:::::::::::::::::::::::::::::::::::::*/
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	Matrix world = Matrix::Identity;
	Matrix CameraMat = camera->GetPose();
	Matrix view = Matrix::CreateLookAt(CameraMat.Translation(), CameraMat.Translation() + CameraMat.Forward(), CameraMat.Up());
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(60.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	// ライトのパラメータ
	Light light;
	light.position = { 100.0f, 100.0f, 100.0f };

	//shader->world(world);
	shader->world(player->GetPose());
	shader->view(view);
	shader->projection(projection);
	shader->light(light);
	//// メッシュの描画
	player->TempDraw(world, view, projection, light);

	stest->world(ptest->GetPose());
	stest->view(view);
	stest->projection(projection);
	stest->light(light);

	ptest->TempDraw(world, view, projection, light);
}


void MyGame::end() {
	m_SceneManager.Finalize();

	delete effect1_;
	delete effect2_;
}