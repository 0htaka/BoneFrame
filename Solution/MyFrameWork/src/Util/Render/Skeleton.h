#ifndef SKELETON_H_
#define SKELETON_H_

#include "Util/Load/ILoadable.h"

#include <string>
#include <vector>
#include "Util/Math/Matrix.h"

class Animation;

class Skeleton {
public:
	struct Bone {
		char			name[32];	// ボーン名
		int				ID;			// ボーンID
		int				parentID;	// 親ボーンID
		Matrix			transform;	// ボーンの変換行列
		Matrix			inverse;	// ボーンの逆行列
	};

public:
	// コンストラクタ
	Skeleton();
	Skeleton(const std::string& filePath);
	// ボーン数を返す
	std::size_t Size() const;
	// ボーンのローカル変換行列を計算する
	void CalculateLocalMatrices(Animation& animation, float animTime, Matrix local[]) const;
	// ボーンのローカル変換行列を計算する
	// void CalculateLocalMatrices(const Animation& animation, float animTime, Matrix local[]) const;
	// ボーンのワールド変換行列を計算する
	void CalculateWorldMatrices(const Matrix& parent, const Matrix local[], Matrix world[]) const;
	// スキニング用の変換行列を計算する
	void CalculateSkinnedMatrices(const Matrix world[], Matrix skinned[]) const;
	// 消去
	void Clear();
	// ファイル読み込み
	void Load(const std::string& fileName);
private:
	// ボーン配列
	std::vector<Bone>	bones_;
};

#endif
