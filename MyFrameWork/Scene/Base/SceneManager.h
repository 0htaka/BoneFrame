#ifndef	 _SCENE_MANAGER_H_
#define	 _SCENE_MANAGER_H_

enum class Scenes;
#include"SceneBasePtr.h"
#include<unordered_map>

//�V�[���}�l�[�W���[
class SceneManager
{
public:
	//�R���X�g���N�^
	SceneManager();
	//������
	void Initialize();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw();
	//�I��
	void Finalize();
	//�I��������
	bool IsEnd() const;
	//�V�[���̒ǉ�
	void Add(Scenes name, const ScenePtr& scene);
	//�V�[���̕ύX
	void Change(Scenes name);

	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	SceneManager operator=(const SceneManager& other) = delete;
private:
	//�V�[��
	std::unordered_map<Scenes, ScenePtr>	m_Scenes;
	//���݂̃V�[��
	ScenePtr								m_CurrentScene;
	//Sprite m_fadeSprite;

	bool m_bChangeScene;
};

#endif