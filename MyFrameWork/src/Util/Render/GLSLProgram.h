#ifndef GLSL_PROGRAM_H_
#define GLSL_PROGRAM_H_

#include <opengl_ext.h>
#include <string>

//�o�[�e�b�N�X�A�s�N�Z���V�F�[�_���R���p�C���A�����N���邵�Ǘ�����N���X
class GLSLProgram {
public:
	// �R���X�g���N�^
	GLSLProgram();
	// �f�X�g���N�^
	~GLSLProgram();
	// �V�F�[�_�[�̃R���p�C��
	void compileShader(GLenum type, const std::string& fileName);
	// �V�F�[�_�[�̃����N
	void link();
	// �v���O�����̊J�n
	void begin();
	// �v���O�����̏I��
	void end();
	// �V�F�[�_�[�p�����[�^�̎擾
	GLint uniform(const std::string& name) const;
	// �A�g���r���[�g�̎擾
	GLint attribute(const std::string& name) const;

	// �R�s�[�֎~
	GLSLProgram(const GLSLProgram& other) = delete;
	GLSLProgram& operator = (const GLSLProgram& other) = delete;
private:
	// GLSL�v���O����
	GLuint program_;
};

#endif

