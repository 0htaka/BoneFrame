#ifndef EFFECT_GL_H_
#define EFFECT_GL_H_

#include <string>
#include "GLSLProgram.h"
#include "Util/Math/Vector2.h"
#include "Util/Math/Vector3.h"
#include "Util/Math/Color.h"
#include "Util/Math/Matrix.h"

//�v���O�������ƃV�F�[�_���̃p�����[�^���̘A�g��}��N���X
class EffectGL {
public:
	// �R���X�g���N�^
	EffectGL(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);
	// �R���X�g���N�^
	EffectGL(GLSLShader& vert, GLSLShader& frag);
	// �A�g���r���[�g�̎擾
	GLint attribute(const std::string& name) const;
	// �V�F�[�_�[�p�����[�^�̎擾
	GLint uniform(const std::string& name) const;
	// �V�F�[�_�[��L���ɂ���
	void begin();
	// �V�F�[�_�[�𖳌��ɂ���
	void end();
	// float�̃p�����[�^��ݒ�
	void setParameter(GLuint location, float s);
	// Vector2�̃p�����[�^��ݒ�
	void setParameter(GLuint location, const Vector2& v);
	// Vector3�̃p�����[�^��ݒ�
	void setParameter(GLuint location, const Vector3& v);
	// Color4�̃p�����[�^��ݒ�
	void setParameter(GLuint location, const Color& v);
	// Matrix4�̃p�����[�^��ݒ�
	void setParameter(GLuint location, const Matrix& m);
	// Matrix4�̃p�����[�^��ݒ�
	void setParameter(GLuint location, int num, const Matrix m[]);
	// �e�N�X�`���̃p�����[�^��ݒ�
	void setTexture(GLuint location, GLuint unit);
	// �R�s�[�֎~
	EffectGL(const EffectGL& other) = delete;
	EffectGL& operator = (const EffectGL& other) = delete;
private:
	// GLSL�v���O����
	GLSLProgram program_;
};

#endif
