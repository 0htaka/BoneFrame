#pragma once

#include <opengl_ext.h>
#include "Util/RefPtr.h"
#include <string>
#include <fstream>
#include <vector>
#include "lodepng.h"
#include "Util/Math/Color.h"

class Shader;

struct MyMaterial {
	Color		ambient;						// �����J���[
	Color		diffuse;						// �g�U���ˌ��J���[
	Color		specular;						// ���ʔ��ˌ��J���[
	Color		emission;						// ���ȏƖ��J���[
	float		shiniess;						// ���ʔ��ˎw��
	//�ȍ~���O���[�h�s��
	GLuint			texture;						// �e�N�X�`���I�u�W�F�N�g
	GLuint			normal_texture;					// �@���}�b�v�e�N�X�`���I�u�W�F�N�g
	RefPtr<Shader>	shader;
};

class MaterialLoader {
	using MatPtr = std::unique_ptr<MyMaterial>;
	char		texture_file_path[128];			// �e�N�X�`���t�@�C����
	char		normalTex_file_path[128];	// �@���}�b�v�e�N�X�`���t�@�C����	
	MatPtr material;
public:
	MaterialLoader(const std::string& filePath) {
		std::ifstream file(filePath, std::ios::binary);
		if (!file)
			throw std::runtime_error("can not open " + filePath);

		//�e�N�X�`���t�@�C���p�X�擾
		file.read((char*)this, sizeof(MaterialLoader) - sizeof(material));
		//�}�e���A���̃C���X�^���X����
		material = std::make_unique<MyMaterial>();
		file.read((char*)material.get(), sizeof(MyMaterial));		

		material->texture = createTexture(texture_file_path);
		material->normal_texture = createTexture(normalTex_file_path);
	}
	MatPtr& GetMaterial() {
		return material;
	}
private:
	// �e�N�X�`���̓ǂݍ���
	GLuint createTexture(const std::string& file_name) {
		unsigned int width = 0;
		unsigned int height = 0;
		std::vector<unsigned char> image;
		auto error = lodepng::decode(image, width, height, file_name);
		if (error != 0) {
			throw std::runtime_error("can not open");
		}
		GLuint texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA, width, height,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, image.data()
		);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
};