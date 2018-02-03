#ifndef MESH_SHADER_H_
#define MESH_SHADER_H_

#include "Mesh.h"
#include "Light.h"
#include "EffectGL.h"
#include "Util/Math/Matrix.h"

class MeshShader : public Mesh::Shader {
public:
	// �R���X�g���N�^
	explicit MeshShader(EffectGL& effect);
	// ���[���h�ϊ��s��̐ݒ�
	void world(const Matrix& mat);
	// �r���[�ϊ��s��̐ݒ�
	void view(const Matrix& mat);
	// �����ϊ��s��̐ݒ�
	void projection(const Matrix& mat);
	// ���C�g�̐ݒ�
	void light(const Light& light);
	// �V�F�[�_�[�̊J�n
	virtual void begin() override;
	// �V�F�[�_�[�̏I��
	virtual void end() override;
	// �}�e���A���̐ݒ�
	virtual void material(const Mesh::Material& material);

protected:
	// �V�F�[�_�[�N���X
	EffectGL*		effect_;
	// ���[���h�ϊ��s��
	Matrix			world_;
	// �r���[�ϊ��s��
	Matrix			view_;
	// �����ϊ��s��
	Matrix			projection_;
	// �}�e���A��
	Mesh::Material	material_;
	// ���C�g
	Light			light_;
};

#endif

