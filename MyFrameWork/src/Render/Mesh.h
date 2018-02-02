#ifndef MESH_H_
#define MESH_H_

#include"Load\ILoadable.h"

#include <opengl_ext.h>
#include <vector>
#include <string>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Color.h"

class Mesh {
public:
	// �}�e���A���\����
	struct Material {
		Color		ambient;						// �����J���[
		Color		diffuse;						// �g�U���ˌ��J���[
		Color		specular;						// ���ʔ��ˌ��J���[
		Color		emission;						// ���ȏƖ��J���[
		float		shiniess;						// ���ʔ��ˎw��
		char		texture_file_name[128];			// �e�N�X�`���t�@�C����
		char		normal_texture_file_name[128];	// �@���}�b�v�e�N�X�`���t�@�C����
		GLuint		texture;						// �e�N�X�`���I�u�W�F�N�g
		GLuint		normal_texture;					// �@���}�b�v�e�N�X�`���I�u�W�F�N�g
	};
	// �T�u�Z�b�g�\����
	struct Subset {
		int			material;						// �}�e���A���ԍ�
		int			start;							// �C���f�b�N�X�̊J�n�ʒu
		int			count;							// �C���f�b�N�X��
	};
	// ���_�f�[�^�\����
	struct Vertex {
		Vector3			position;					// ���W
		Vector3			normal;						// �@��
		Vector2			texcoord;					// �e�N�X�`�����W
		unsigned char	bone_indices[4];			// �{�[���C���f�b�N�X
		float			bone_weights[4];			// �{�[���E�F�C�g
		Vector3			tangent;					// �ڃx�N�g��
		Vector3			binormal;					// �]�@���x�N�g��
	};
	// ���b�V���V�F�[�_�[�N���X
	class Shader {
	public:
		// ���z�f�X�g���N�^
		virtual ~Shader() {}
		// �J�n
		virtual void begin() = 0;
		// �I��
		virtual void end() = 0;
		// �}�e���A���̐ݒ�
		virtual void material(const Mesh::Material& material) = 0;
	};

public:
	// �R���X�g���N�^
	Mesh();
	Mesh(const std::string& filePath);
	// �f�X�g���N�^
	~Mesh();
	// �`��
	void Draw(Mesh::Shader& shader) const;
	// �t�@�C���̓ǂݍ���
	void Load(const std::string& file_name);
	// ����
	void Clear();


	// ���[�u�R���X�g���N�^
	Mesh(Mesh&& other) = default;
	// �R�s�[�֎~
	Mesh(const Mesh&) = delete;
	Mesh& operator = (const Mesh&) = delete;

private:
	// �e�N�X�`���̓ǂݍ���
	GLuint	createTexture(const std::string& file_name);
	// �o�b�t�@�I�u�W�F�N�g�Ƀf�[�^���Z�b�g
	void setToBuffer(GLenum target, GLenum& buffer, GLuint size, const GLvoid* data);
	// ���_�z��I�u�W�F�N�g�̍쐬
	void createVertexArray();
private:
	// �}�e���A���z��
	std::vector<Material>	materials_;
	// �T�u�Z�b�g�z��
	std::vector<Subset>		subsets_;
	// �C���f�b�N�X�o�b�t�@
	GLuint		indices_{ 0 };
	// ���_�o�b�t�@
	GLuint		vertices_{ 0 };
	// ���_�f�[�^�z��
	GLuint		vertexArray_{ 0 };
};

#endif

