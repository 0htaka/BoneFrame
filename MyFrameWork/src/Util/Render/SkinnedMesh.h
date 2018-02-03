#ifndef SKINNED_MESH_H_
#define SKINNED_MESH_H_

#include "Mesh.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Util/Math/Matrix.h"

// スキニングメッシュクラス
class SkinnedMesh {
public:
	// スキニングメッシュシェーダー
	class Shader : public Mesh::Shader {
	public:
		// 仮想デストラクタ
		virtual ~Shader() {}
		// ボーンの変換行列を設定
		virtual void boneMetrices(int size, const Matrix matrices[]) = 0;
	};
public:
	// コンストラクタ
	SkinnedMesh(Mesh& mesh, Skeleton& skeleton, Animation& animation);
	// 計算
	void caluclate(const Matrix& world, float deltSec);
	// 描画
	void draw(SkinnedMesh::Shader& shader) const;

private:
	// ボーンの最大数
	static const unsigned int BONE_MAX = 256;
	// メッシュ
	const Mesh*			mesh_;
	// スケルトン
	const Skeleton*		skeleton_;
	// アニメーション
	const Animation*	animation_;
	// ローカル変換行列
	Matrix			localMatrices_[BONE_MAX];
	// ワールド変換行列
	Matrix			worldMatrices_[BONE_MAX];
	// スキニング変換行列
	Matrix			skinnedMatrices_[BONE_MAX];
};

#endif
