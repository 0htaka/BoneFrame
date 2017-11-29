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
	skeleton_->calculateLocalMatrices(*animation_, frameNo, localMatrices_);
	// ワールド変換行列の計算
	skeleton_->calculateWorldMatrices(world, localMatrices_, worldMatrices_);
	// スキニング用の変換行列の計算
	skeleton_->calculateSkinnedMatrices(worldMatrices_, skinnedMatrices_);
}

// 描画
void SkinnedMesh::draw(SkinnedMesh::Shader & shader) const {
	shader.boneMetrices(skeleton_->size(), skinnedMatrices_);
	mesh_->draw(shader);
}
