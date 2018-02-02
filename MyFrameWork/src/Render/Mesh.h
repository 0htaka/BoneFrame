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
	// マテリアル構造体
	struct Material {
		Color		ambient;						// 環境光カラー
		Color		diffuse;						// 拡散反射光カラー
		Color		specular;						// 鏡面反射光カラー
		Color		emission;						// 自己照明カラー
		float		shiniess;						// 鏡面反射指数
		char		texture_file_name[128];			// テクスチャファイル名
		char		normal_texture_file_name[128];	// 法線マップテクスチャファイル名
		GLuint		texture;						// テクスチャオブジェクト
		GLuint		normal_texture;					// 法線マップテクスチャオブジェクト
	};
	// サブセット構造体
	struct Subset {
		int			material;						// マテリアル番号
		int			start;							// インデックスの開始位置
		int			count;							// インデックス数
	};
	// 頂点データ構造体
	struct Vertex {
		Vector3			position;					// 座標
		Vector3			normal;						// 法線
		Vector2			texcoord;					// テクスチャ座標
		unsigned char	bone_indices[4];			// ボーンインデックス
		float			bone_weights[4];			// ボーンウェイト
		Vector3			tangent;					// 接ベクトル
		Vector3			binormal;					// 従法線ベクトル
	};
	// メッシュシェーダークラス
	class Shader {
	public:
		// 仮想デストラクタ
		virtual ~Shader() {}
		// 開始
		virtual void begin() = 0;
		// 終了
		virtual void end() = 0;
		// マテリアルの設定
		virtual void material(const Mesh::Material& material) = 0;
	};

public:
	// コンストラクタ
	Mesh();
	Mesh(const std::string& filePath);
	// デストラクタ
	~Mesh();
	// 描画
	void Draw(Mesh::Shader& shader) const;
	// ファイルの読み込み
	void Load(const std::string& file_name);
	// 消去
	void Clear();


	// ムーブコンストラクタ
	Mesh(Mesh&& other) = default;
	// コピー禁止
	Mesh(const Mesh&) = delete;
	Mesh& operator = (const Mesh&) = delete;

private:
	// テクスチャの読み込み
	GLuint	createTexture(const std::string& file_name);
	// バッファオブジェクトにデータをセット
	void setToBuffer(GLenum target, GLenum& buffer, GLuint size, const GLvoid* data);
	// 頂点配列オブジェクトの作成
	void createVertexArray();
private:
	// マテリアル配列
	std::vector<Material>	materials_;
	// サブセット配列
	std::vector<Subset>		subsets_;
	// インデックスバッファ
	GLuint		indices_{ 0 };
	// 頂点バッファ
	GLuint		vertices_{ 0 };
	// 頂点データ配列
	GLuint		vertexArray_{ 0 };
};

#endif

