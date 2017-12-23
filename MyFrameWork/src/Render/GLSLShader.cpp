#include "GLSLShader.h"
#include <opengl_ext.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

GLSLShader::GLSLShader(GLenum type, const std::string & fileName) :
	type_(type), shader_(0) {
	shader_ = glCreateShader(type);
	compile(fileName);
}

GLSLShader::~GLSLShader() {
	glDeleteShader(shader_);
}

GLenum GLSLShader::type() const {
	return type_;
}

GLenum GLSLShader::shader() const {
	return shader_;
}

void GLSLShader::compile(const std::string & fileName) {
	const std::vector<char> program(load(fileName));
	const GLchar* string = program.data();
	const GLint size = program.size();
	glShaderSource(shader_, 1, &string, &size);
	glCompileShader(shader_);
	// �R���p�C���G���[�̃`�F�b�N
	GLint compiled = 0;
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		// �R���p�C���G���[���o��
		GLint length = 0;
		glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(shader_, (GLsizei)log.size(), 0, &log[0]);
		glDeleteShader(shader_);
		shader_ = 0;
		OutputDebugStringA("glsl compile error");
		OutputDebugStringA(fileName.c_str());
		OutputDebugStringA("\n");
		OutputDebugStringA(log.data());
		throw std::runtime_error("glsl compile error" + fileName);
	}
}

std::vector<char> GLSLShader::load(const std::string & fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file) throw std::runtime_error("can not open" + fileName);
	// �t�@�C���T�C�Y�̎擾
	file.seekg(0, std::ios_base::end);
	std::size_t size = (std::size_t)file.tellg();
	file.seekg(0, std::ios_base::beg);
	// �V�F�[�_�[�t�@�C�����o�b�t�@�ɓǂݍ���
	std::vector<char> program(size);
	file.read(program.data(), size);
	return program;
}
