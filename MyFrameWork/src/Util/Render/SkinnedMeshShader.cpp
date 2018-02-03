#include "SkinnedMeshShader.h"
#include <algorithm>

SkinnedMeshShader::SkinnedMeshShader(EffectGL & effect) :
	MeshShader(effect), numBones_(0) {
}

void SkinnedMeshShader::begin() {
	MeshShader::begin();
	effect_->setParameter(effect_->uniform("u_matBones"), numBones_, &boneMatrices_[0]);
}

void SkinnedMeshShader::end() {
	MeshShader::end();
}

void SkinnedMeshShader::material(const Mesh::Material & material) {
	MeshShader::material(material);
}

void SkinnedMeshShader::boneMetrices(int size, const Matrix matrices[]) {
	numBones_ = size;
	std::copy(&matrices[0], &matrices[size], boneMatrices_);
}
