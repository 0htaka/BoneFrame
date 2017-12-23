#include "SkinnedMesh.h"

// �R���X�g���N�^
SkinnedMesh::SkinnedMesh(Mesh & mesh, Skeleton & skeleton, Animation & animation) :
	mesh_(&mesh),
	skeleton_(&skeleton),
	animation_(&animation) {
}

// �v�Z
void SkinnedMesh::caluclate(const Matrix& world, float frameNo) {
	// �A�j���[�V�����ϊ��s��̌v�Z
	skeleton_->CalculateLocalMatrices(*animation_, frameNo, localMatrices_);
	// ���[���h�ϊ��s��̌v�Z
	skeleton_->CalculateWorldMatrices(world, localMatrices_, worldMatrices_);
	// �X�L�j���O�p�̕ϊ��s��̌v�Z
	skeleton_->CalculateSkinnedMatrices(worldMatrices_, skinnedMatrices_);
}

// �`��
void SkinnedMesh::draw(SkinnedMesh::Shader & shader) const {
	shader.boneMetrices(skeleton_->Size(), skinnedMatrices_);
	mesh_->Draw(shader);
}
