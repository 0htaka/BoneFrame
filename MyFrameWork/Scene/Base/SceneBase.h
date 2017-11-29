#ifndef	_ISCENE_H_
#define	_ISCENE_H_

enum class Scenes;
#include<vector>

//シーンインターフェース
class SceneBase
{
public:
	SceneBase();
	//仮想デストラクタ
	virtual ~SceneBase(){}
	//開始
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	//描画
	virtual void Draw()const = 0;
	//終了しているか
	virtual bool IsEnd()const = 0;
	//次のシーンを返す
	virtual Scenes GetNextScene()const = 0;
	//使用するアセットのパス群を取得
	virtual std::vector<std::string> GetUseAssetPaths() const = 0;
	//終了
	virtual void Finalize() = 0;
	
protected:
	bool m_bSceneEnd;
};

#endif