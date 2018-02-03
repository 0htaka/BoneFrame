// Animation.h
#ifndef ANIMATION_H_
#define	ANIMATION_H_

#include"Util/Load/ILoadable.h"

#include <vector>
#include <unordered_map>
#include <string>
#include "Util/Math/Matrix.h"
#include "Util/Math/Vector3.h"
#include "Util/Math/Quaternion.h"

// アニメーションクラス
class Animation {
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
	Animation(const std::string& filePath);
	// キーフレームの取得
	KeyFrame GetKeyFrame(const std::string& boneName, float frameNo) const;
	// 消去
	void Clear();
	// ファイルから読み込む
	void Load(const std::string& fileName);
	// 終了フレーム数を返す
	float EndTime() const;
private:
	// ボーンキーフレーム
	std::unordered_map<std::string, std::vector<KeyFrame>> mBoneKeyFrames;
	//アニメーションのサンプル数
	int FPS{ 30 };
};

#endif

