#include "SkinnedMesh.h"

// コンストラクタ
SkinnedMesh::SkinnedMesh(Mesh & mesh, Skeleton & skeleton, Animation & animation) :
	mesh_(&mesh),
	skeleton_(&skeleton),
	animation_(&animation) {
}

// 計算
void SkinnedMesh::caluclate(const Matrix& world, float frameNo) {
	// アニメーション変換行列の計算
	skeleton_->CalculateLocalMatrices(*animation_, frameNo, localMatrices_);
	// ワールド変換行列の計算
	skeleton_->CalculateWorldMatrices(world, localMatrices_, worldMatrices_);
	// スキニング用の変換行列の計算
	skeleton_->CalculateSkinnedMatrices(worldMatrices_, skinnedMatrices_);
}

// 描画
void SkinnedMesh::draw(SkinnedMesh::Shader & shader) const {
	shader.boneMetrices(skeleton_->Size(), skinnedMatrices_);
	mesh_->Draw(shader);
}
