// Animation.h
#ifndef ANIMATION_H_
#define	ANIMATION_H_

#include"AssetManager/Base/ILoadable.h"

#include <vector>
#include <unordered_map>
#include <string>
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

// アニメーションクラス
class Animation : public ILoadable {
public:
	struct KeyFrame {					// キーフレーム構造体
		float		frameNo;			// フレーム番号
		Vector3		scale;				// 拡大縮小
		Quaternion	rotate;				// 回転
		Vector3		position;			// 平行移動
		Matrix		matrix() const;		// 変換行列を計算する
	};
public:
	// コンストラクタ
	Animation();
	// キーフレームの取得
	KeyFrame GetKeyFrame(const std::string& boneName, float frameNo) const;
	// 消去
	void Clear();
	// ファイルから読み込む
	void Load(const std::string& fileName) override;
	// 終了フレーム数を返す
	float EndFrame() const;
private:
	// ボーンキーフレーム
	std::unordered_map<std::string, std::vector<KeyFrame>> boneKeyFrames_;
};

#endif

