#pragma once

#include"Base\SceneBase.h"
#include"Base\Scenes.h"
#include"Actor\Player.h"


class TestScene : public SceneBase
{
public:
	TestScene() {}
	~TestScene() {}

	//�J�n
	virtual void Initialize()override {}
	//�X�V
	virtual void Update(float deltaTime) override {}
	//�`��
	virtual void Draw()const override 
	{
		
	}
	//�I�����Ă��邩
	virtual bool IsEnd()const override { return false; }
	//���̃V�[����Ԃ�
	virtual Scenes GetNextScene()const override { return Scenes::Null; }

	std::vector<std::string> GetUseAssetPaths() const{
		return std::vector<std::string>();
	}
	//�I��
	virtual void Finalize() override {}
private:
};