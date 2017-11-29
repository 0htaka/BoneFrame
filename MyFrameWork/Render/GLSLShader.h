#ifndef GLSL_SHADER_H_
#define GLSL_SHADER_H_

#include <opengl_ext.h>
#include <string>
#include <vector>

// GLSL�V�F�[�_�[�N���X
class GLSLShader {
public:
	// �R���X�g���N�^
	GLSLShader(GLenum type, const std::string& fileName);
	// �f�X�g���N�^
	~GLSLShader();
	// �V�F�[�_�[�^�C�v�̎擾
	GLenum type() const;
	// �V�F�[�_�[�̎擾
	GLenum shader() const;

private:
	// �V�F�[�_�[�̃R���p�C��
	void compile(const std::string& fileName);
	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	std::vector<char> load(const std::string& fileName);
	// �R�s�[�֎~
	GLSLShader(const GLSLShader& other) = delete;
	GLSLShader& operator = (const GLSLShader& other) = delete;

private:
	// �V�F�[�_�[�^�C�v
	GLenum	type_;
	// �V�F�[�_�[
	GLenum	shader_;
};

#endif

