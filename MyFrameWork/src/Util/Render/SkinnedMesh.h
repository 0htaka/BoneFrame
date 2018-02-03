#ifndef SKINNED_MESH_H_
#define SKINNED_MESH_H_

#include "Mesh.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Util/Math/Matrix.h"

// �X�L�j���O���b�V���N���X
class SkinnedMesh {
public:
	// �X�L�j���O���b�V���V�F�[�_�[
	class Shader : public Mesh::Shader {
	public:
		// ���z�f�X�g���N�^
		virtual ~Shader() {}
		// �{�[���̕ϊ��s���ݒ�
		virtual void boneMetrices(int size, const Matrix matrices[]) = 0;
	};
public:
	// �R���X�g���N�^
	SkinnedMesh(Mesh& mesh, Skeleton& skeleton, Animation& animation);
	// �v�Z
	void caluclate(const Matrix& world, float deltSec);
	// �`��
	void draw(SkinnedMesh::Shader& shader) const;

private:
	// �{�[���̍ő吔
	static const unsigned int BONE_MAX = 256;
	// ���b�V��
	const Mesh*			mesh_;
	// �X�P���g��
	const Skeleton*		skeleton_;
	// �A�j���[�V����
	const Animation*	animation_;
	// ���[�J���ϊ��s��
	Matrix			localMatrices_[BONE_MAX];
	// ���[���h�ϊ��s��
	Matrix			worldMatrices_[BONE_MAX];
	// �X�L�j���O�ϊ��s��
	Matrix			skinnedMatrices_[BONE_MAX];
};

#endif
