#ifndef SKINNED_MESH_SHADER_H_
#define SKINNED_MESH_SHADER_H_

#include "SkinnedMesh.h"
#include "MeshShader.h"

class SkinnedMeshShader : public MeshShader, public SkinnedMesh::Shader {
public:
	// �R���X�g���N�^
	explicit SkinnedMeshShader(EffectGL& effect);
	// �J�n
	virtual void begin() override;
	// �I��
	virtual void end() override;
	// �}�e���A���̐ݒ�
	virtual void material(const Mesh::Material& material) override;
	// �{�[���̕ϊ��s���ݒ�
	virtual void boneMetrices(int size, const Matrix matrices[]) override;
private:
	// �{�[���̍ő吔
	static const unsigned int BONE_MAX = 256;
	// �{�[����
	int numBones_;
	// �{�[���̕ϊ��s��
	Matrix boneMatrices_[BONE_MAX];
};

#endif
