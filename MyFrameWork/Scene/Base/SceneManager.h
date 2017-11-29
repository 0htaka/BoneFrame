#ifndef	 _SCENE_MANAGER_H_
#define	 _SCENE_MANAGER_H_

enum class Scenes;
#include"SceneBasePtr.h"
#include<unordered_map>

//シーンマネージャー
class SceneManager
{
public:
	//コンストラクタ
	SceneManager();
	//初期化
	void Initialize();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw();
	//終了
	void Finalize();
	//終了したか
	bool IsEnd() const;
	//シーンの追加
	void Add(Scenes name, const ScenePtr& scene);
	//シーンの変更
	void Change(Scenes name);

	//コピー禁止
	SceneManager(const SceneManager& other) = delete;
	SceneManager operator=(const SceneManager& other) = delete;
private:
	//シーン
	std::unordered_map<Scenes, ScenePtr>	m_Scenes;
	//現在のシーン
	ScenePtr								m_CurrentScene;
	//Sprite m_fadeSprite;

	bool m_bChangeScene;
};

#endif