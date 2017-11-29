#pragma once

#include"Base\SceneBase.h"
#include"Base\Scenes.h"
#include"Actor\Player.h"


class TestScene : public SceneBase
{
public:
	TestScene() {}
	~TestScene() {}

	//開始
	virtual void Initialize()override {}
	//更新
	virtual void Update(float deltaTime) override {}
	//描画
	virtual void Draw()const override 
	{
		
	}
	//終了しているか
	virtual bool IsEnd()const override { return false; }
	//次のシーンを返す
	virtual Scenes GetNextScene()const override { return Scenes::Null; }

	std::vector<std::string> GetUseAssetPaths() const{
		return std::vector<std::string>();
	}
	//終了
	virtual void Finalize() override {}
private:
};