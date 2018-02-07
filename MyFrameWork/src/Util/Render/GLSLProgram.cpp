#include "GLSLProgram.h"
#include "GLSLShader.h"


GLSLProgram::GLSLProgram() : program_(0) {
	program_ = glCreateProgram();
}

GLSLProgram::~GLSLProgram() {
	glDeleteProgram(program_);
}

void GLSLProgram::compileShader(GLenum type, const std::string & fileName) {
	// シェーダーの作成
	const GLSLShader shader(type, fileName);
	// シェーダーのアタッチ
	glAttachShader(program_, shader.shader());
}

void GLSLProgram::link() {
	glLinkProgram(program_);
	// リンクエラーの確認
	GLint linked = 0;
	glGetProgramiv(program_, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		// リンクエラーの出力
		GLint length = 0;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(program_, (GLsizei)log.size(), 0, log.data());
		OutputDebugStringA("glsl link error");
		OutputDebugStringA(log.data());
		throw std::runtime_error("glsl link error");
	}
}

void GLSLProgram::link(GLSLShader & vert, GLSLShader & frag) {
	// シェーダーのアタッチ
	glAttachShader(program_, vert.shader());
	// シェーダーのアタッチ
	glAttachShader(program_, frag.shader());
	link();
}

void GLSLProgram::begin() {
	glUseProgram(program_);
}

void GLSLProgram::end() {
	glUseProgram(0);
}

GLint GLSLProgram::uniform(const std::string & name) const {
	return glGetUniformLocation(program_, name.c_str());
}

GLint GLSLProgram::attribute(const std::string & name) const {
	return glGetAttribLocation(program_, name.c_str());
}
