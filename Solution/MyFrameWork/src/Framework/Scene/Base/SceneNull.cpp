#include"SceneNull.h"

#include"Scenes.h"
//�J�n
void SceneNull::Initialize()
{
}
//�X�V
void SceneNull::Update(float deltaTime)
{
	(void)deltaTime;
}
//�`��
void SceneNull::Draw()const{}
//�I�����Ă��邩
bool SceneNull::IsEnd()const
{
	return false;
}
//���̃V�[����Ԃ�
Scenes SceneNull::GetNextScene()const
{
	return Scenes::Null;
}
std::vector<std::string> SceneNull::GetUseAssetPaths() const
{
	return std::vector<std::string>();
}
//�I��
void SceneNull::Finalize(){}