#include"SceneManager.h"
#include"SceneNull.h"

#include"Screen/Screen.h"
#include"Input/Input.h"

//コンストラクタ
SceneManager::SceneManager() :
	m_CurrentScene(std::make_shared<SceneNull>()),
	m_bChangeScene(false)
{
}
//初期化
void SceneManager::Initialize()
{
	Finalize();
	m_Scenes.clear();
}
//更新
void SceneManager::Update(float deltaTime)
{
	//インプットの更新
	//Input::GetInstance().Update();
	if (m_bChangeScene)
	{
		m_bChangeScene = false;
		Change(m_CurrentScene->GetNextScene());
		return;
	}

	m_CurrentScene->Update(deltaTime);

	if (!m_bChangeScene && m_CurrentScene->IsEnd())	
		m_bChangeScene = true;	
}

//描画
void SceneManager::Draw()
{
	m_CurrentScene->Draw();	
}

//終了
void SceneManager::Finalize()
{
	m_CurrentScene->Finalize();
	m_CurrentScene = std::make_shared<SceneNull>();
}

bool SceneManager::IsEnd() const
{
	return false;
}

//シーンの追加
void SceneManager::Add(Scenes name, const ScenePtr& scene)
{
	m_Scenes[name] = scene;
}
//シーンの変更
void SceneManager::Change(Scenes name)
{
	Finalize();
	m_CurrentScene = m_Scenes[name];
	m_CurrentScene->Initialize();	
}