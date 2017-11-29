#ifndef SKELETON_H_
#define SKELETON_H_

#include <string>
#include <vector>
#include "Math/Matrix.h"

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
	// ボーン数を返す
	std::size_t size() const;
	// ボーンのローカル変換行列を計算する
	void calculateLocalMatrices(const Animation& animation, float frameNo, Matrix local[]) const;
	// ボーンのワールド変換行列を計算する
	void calculateWorldMatrices(const Matrix& parent, const Matrix local[], Matrix world[]) const;
	// スキニング用の変換行列を計算する
	void calculateSkinnedMatrices(const Matrix world[], Matrix skinned[]) const;
	// 消去
	void clear();
	// ファイル読み込み
	void load(const std::string& fileName);
private:
	// ボーン配列
	std::vector<Bone>	bones_;
};

#endif
