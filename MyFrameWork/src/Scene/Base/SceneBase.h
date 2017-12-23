#ifndef	_ISCENE_H_
#define	_ISCENE_H_

enum class Scenes;
#include<vector>

//�V�[���C���^�[�t�F�[�X
class SceneBase
{
public:
	SceneBase();
	//���z�f�X�g���N�^
	virtual ~SceneBase(){}
	//�J�n
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	//�`��
	virtual void Draw()const = 0;
	//�I�����Ă��邩
	virtual bool IsEnd()const = 0;
	//���̃V�[����Ԃ�
	virtual Scenes GetNextScene()const = 0;
	//�g�p����A�Z�b�g�̃p�X�Q���擾
	virtual std::vector<std::string> GetUseAssetPaths() const = 0;
	//�I��
	virtual void Finalize() = 0;
	
protected:
	bool m_bSceneEnd;
};

#endif