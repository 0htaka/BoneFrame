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
	skeleton_->calculateLocalMatrices(*animation_, frameNo, localMatrices_);
	// ���[���h�ϊ��s��̌v�Z
	skeleton_->calculateWorldMatrices(world, localMatrices_, worldMatrices_);
	// �X�L�j���O�p�̕ϊ��s��̌v�Z
	skeleton_->calculateSkinnedMatrices(worldMatrices_, skinnedMatrices_);
}

// �`��
void SkinnedMesh::draw(SkinnedMesh::Shader & shader) const {
	shader.boneMetrices(skeleton_->size(), skinnedMatrices_);
	mesh_->draw(shader);
}
