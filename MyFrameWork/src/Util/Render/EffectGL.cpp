#include "EffectGL.h"
#include "GLSLShader.h"
#include <opengl_ext.h>

EffectGL::EffectGL(const std::string & vertexShaderFileName, const std::string & fragmentShaderFileName) {
	program_.compileShader(GL_VERTEX_SHADER, vertexShaderFileName);
	program_.compileShader(GL_FRAGMENT_SHADER, fragmentShaderFileName);
	program_.link();
}

EffectGL::EffectGL(GLSLShader & vert, GLSLShader & frag) {

}

GLint EffectGL::attribute(const std::string & name) const {
	return program_.attribute(name);
}

GLint EffectGL::uniform(const std::string & name) const {
	return program_.uniform(name);
}

void EffectGL::begin() {
	program_.begin();
}

void EffectGL::end() {
	program_.end();
}

void EffectGL::setParameter(GLuint location, float s) {
	glUniform1f(location, s);
}

void EffectGL::setParameter(GLuint location, const Vector2& v) {
	glUniform2f(location, v.x, v.y);
}

void EffectGL::setParameter(GLuint location, const Vector3& v){
	glUniform3f(location, v.x, v.y, v.z);
}

void EffectGL::setParameter(GLuint location, const Color& v) {
	glUniform4f(location, v.r, v.g, v.b, v.a);
}

void EffectGL::setParameter(GLuint location, const Matrix& m) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &m.m[0][0]);
}

void EffectGL::setParameter(GLuint location, int num ,const Matrix m[]) {
	glUniformMatrix4fv(location, num, GL_FALSE, &m[0].m[0][0]);
}

void EffectGL::setTexture(GLuint location, GLuint unit) {
	glUniform1i(location, unit);
}
