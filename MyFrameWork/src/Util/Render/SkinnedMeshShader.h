#ifndef SKINNED_MESH_SHADER_H_
#define SKINNED_MESH_SHADER_H_

#include "SkinnedMesh.h"
#include "MeshShader.h"

class SkinnedMeshShader : public MeshShader, public SkinnedMesh::Shader {
public:
	// コンストラクタ
	explicit SkinnedMeshShader(EffectGL& effect);
	// 開始
	virtual void begin() override;
	// 終了
	virtual void end() override;
	// マテリアルの設定
	virtual void material(const Mesh::Material& material) override;
	// ボーンの変換行列を設定
	virtual void boneMetrices(int size, const Matrix matrices[]) override;
private:
	// ボーンの最大数
	static const unsigned int BONE_MAX = 256;
	// ボーン数
	int numBones_;
	// ボーンの変換行列
	Matrix boneMatrices_[BONE_MAX];
};

#endif
