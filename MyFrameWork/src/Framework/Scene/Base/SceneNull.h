#ifndef	_SCENE_NULL_H_
#define	_SCENE_NULL_H_

#include "SceneBase.h"

//��̃V�[��
class SceneNull :public SceneBase
{
public:
	//�J�n
	virtual void Initialize()override;
	//�X�V
	virtual void Update(float deltaTime)override;
	//�`��
	virtual void Draw()const override;
	//�I�����Ă��邩
	virtual bool IsEnd()const override;
	//���̃V�[����Ԃ�
	virtual Scenes GetNextScene()const override;

	virtual std::vector<std::string> GetUseAssetPaths() const;
	//�I��
	virtual void Finalize() override;
};

#endif