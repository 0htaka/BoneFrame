#include"SceneNull.h"

#include"Scenes.h"
//開始
void SceneNull::Initialize()
{
}
//更新
void SceneNull::Update(float deltaTime)
{
	(void)deltaTime;
}
//描画
void SceneNull::Draw()const{}
//終了しているか
bool SceneNull::IsEnd()const
{
	return false;
}
//次のシーンを返す
Scenes SceneNull::GetNextScene()const
{
	return Scenes::Null;
}
std::vector<std::string> SceneNull::GetUseAssetPaths() const
{
	return std::vector<std::string>();
}
//終了
void SceneNull::Finalize(){}