#ifndef MESH_SHADER_H_
#define MESH_SHADER_H_

#include "Mesh.h"
#include "Light.h"
#include "EffectGL.h"
#include "Util/Math/Matrix.h"

class MeshShader : public Mesh::Shader {
public:
	// コンストラクタ
	explicit MeshShader(EffectGL& effect);
	// ワールド変換行列の設定
	void world(const Matrix& mat);
	// ビュー変換行列の設定
	void view(const Matrix& mat);
	// 透視変換行列の設定
	void projection(const Matrix& mat);
	// ライトの設定
	void light(const Light& light);
	// シェーダーの開始
	virtual void begin() override;
	// シェーダーの終了
	virtual void end() override;
	// マテリアルの設定
	virtual void material(const Mesh::Material& material);

protected:
	// シェーダークラス
	EffectGL*		effect_;
	// ワールド変換行列
	Matrix			world_;
	// ビュー変換行列
	Matrix			view_;
	// 透視変換行列
	Matrix			projection_;
	// マテリアル
	Mesh::Material	material_;
	// ライト
	Light			light_;
};

#endif

