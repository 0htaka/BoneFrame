#ifndef GLSL_PROGRAM_H_
#define GLSL_PROGRAM_H_

#include <opengl_ext.h>
#include <string>

//バーテックス、ピクセルシェーダをコンパイル、リンクするし管理するクラス
class GLSLProgram {
public:
	// コンストラクタ
	GLSLProgram();
	// デストラクタ
	~GLSLProgram();
	// シェーダーのコンパイル
	void compileShader(GLenum type, const std::string& fileName);
	// シェーダーのリンク
	void link();
	// プログラムの開始
	void begin();
	// プログラムの終了
	void end();
	// シェーダーパラメータの取得
	GLint uniform(const std::string& name) const;
	// アトリビュートの取得
	GLint attribute(const std::string& name) const;

	// コピー禁止
	GLSLProgram(const GLSLProgram& other) = delete;
	GLSLProgram& operator = (const GLSLProgram& other) = delete;
private:
	// GLSLプログラム
	GLuint program_;
};

#endif

