#ifndef GLSL_SHADER_H_
#define GLSL_SHADER_H_

#include <opengl_ext.h>
#include <string>
#include <vector>

// GLSLシェーダークラス
class GLSLShader {
public:
	// コンストラクタ
	GLSLShader(GLenum type, const std::string& fileName);
	// デストラクタ
	~GLSLShader();
	// シェーダータイプの取得
	GLenum type() const;
	// シェーダーの取得
	GLenum shader() const;

private:
	// シェーダーのコンパイル
	void compile(const std::string& fileName);
	// シェーダーファイルの読み込み
	std::vector<char> load(const std::string& fileName);
	// コピー禁止
	GLSLShader(const GLSLShader& other) = delete;
	GLSLShader& operator = (const GLSLShader& other) = delete;

private:
	// シェーダータイプ
	GLenum	type_;
	// シェーダー
	GLenum	shader_;
};

#endif

