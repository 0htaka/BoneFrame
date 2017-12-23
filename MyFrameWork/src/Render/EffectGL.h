#ifndef EFFECT_GL_H_
#define EFFECT_GL_H_

#include <opengl_ext.h>
#include <string>
#include "GLSLProgram.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Color.h"
#include "Math/Matrix.h"

class EffectGL {
public:
	// コンストラクタ
	EffectGL(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);
	// アトリビュートの取得
	GLint attribute(const std::string& name) const;
	// シェーダーパラメータの取得
	GLint uniform(const std::string& name) const;
	// シェーダーを有効にする
	void begin();
	// シェーダーを無効にする
	void end();
	// floatのパラメータを設定
	void setParameter(GLuint location, float s);
	// Vector2のパラメータを設定
	void setParameter(GLuint location, const Vector2& v);
	// Vector3のパラメータを設定
	void setParameter(GLuint location, const Vector3& v);
	// Color4のパラメータを設定
	void setParameter(GLuint location, const Color& v);
	// Matrix4のパラメータを設定
	void setParameter(GLuint location, const Matrix& m);
	// Matrix4のパラメータを設定
	void setParameter(GLuint location, int num, const Matrix m[]);
	// テクスチャのパラメータを設定
	void setTexture(GLuint location, GLuint unit);
	// コピー禁止
	EffectGL(const EffectGL& other) = delete;
	EffectGL& operator = (const EffectGL& other) = delete;
private:
	// GLSLプログラム
	GLSLProgram program_;
};

#endif

