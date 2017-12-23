#include"SceneManager.h"
#include"SceneNull.h"

#include"Screen/Screen.h"
#include"Input/Input.h"

//�R���X�g���N�^
SceneManager::SceneManager() :
	m_CurrentScene(std::make_shared<SceneNull>()),
	m_bChangeScene(false)
{
}
//������
void SceneManager::Initialize()
{
	Finalize();
	m_Scenes.clear();
}
//�X�V
void SceneManager::Update(float deltaTime)
{
	//�C���v�b�g�̍X�V
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

//�`��
void SceneManager::Draw()
{
	m_CurrentScene->Draw();	
}

//�I��
void SceneManager::Finalize()
{
	m_CurrentScene->Finalize();
	m_CurrentScene = std::make_shared<SceneNull>();
}

bool SceneManager::IsEnd() const
{
	return false;
}

//�V�[���̒ǉ�
void SceneManager::Add(Scenes name, const ScenePtr& scene)
{
	m_Scenes[name] = scene;
}
//�V�[���̕ύX
void SceneManager::Change(Scenes name)
{
	Finalize();
	m_CurrentScene = m_Scenes[name];
	m_CurrentScene->Initialize();	
}