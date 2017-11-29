#include "MeshShader.h"

MeshShader::MeshShader(EffectGL & effect) :
	effect_(&effect) {
}

void MeshShader::world(const Matrix& mat) {
	world_ = mat;
}

void MeshShader::view(const Matrix& mat) {
	view_ = mat;
}

void MeshShader::projection(const Matrix& mat) {
	projection_ = mat;
}

void MeshShader::light(const Light & light) {
	light_ = light;
}

void MeshShader::begin() {
	effect_->begin();
	// 変換行列の設定
	effect_->setParameter(effect_->uniform("u_matWorld"), world_);
	effect_->setParameter(effect_->uniform("u_matView"), view_);
	effect_->setParameter(effect_->uniform("u_matProjection"), projection_);
	// ライトの設定
	effect_->setParameter(effect_->uniform("u_lightPosition"), light_.position * view_);
	effect_->setParameter(effect_->uniform("u_lightAmbient"),  light_.ambient);
	effect_->setParameter(effect_->uniform("u_lightDiffuse"),  light_.diffuse);
	effect_->setParameter(effect_->uniform("u_lightSpecular"), light_.specular);
	// マテリアルの設定
	effect_->setParameter(effect_->uniform("u_materialAmbient"), material_.ambient);
	effect_->setParameter(effect_->uniform("u_materialDiffuse"), material_.diffuse);
	effect_->setParameter(effect_->uniform("u_materialSpecular"), material_.specular);
	effect_->setParameter(effect_->uniform("u_materialEmission"), material_.emission);
	effect_->setParameter(effect_->uniform("u_materialShiniess"), material_.shiniess);
	effect_->setTexture(effect_->uniform("u_baseMap"), 0);
	effect_->setTexture(effect_->uniform("u_normalMap"), 1);
	// テクスチャのバインド
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, material_.normal_texture);	glActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, material_.texture);
}

void MeshShader::end() {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	effect_->end();
}

void MeshShader::material(const Mesh::Material & material) {
	material_ = material;
}
