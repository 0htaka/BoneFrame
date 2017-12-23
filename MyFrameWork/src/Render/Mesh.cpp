#include "Mesh.h"
#include "lodepng.h"
#include <fstream>
#include <vector>
#include <filesystem>

// �f�X�g���N�^
Mesh::~Mesh() {
	Clear();
}

void Mesh::Draw(Mesh::Shader& shader) const {
	// ���_�z��̃o�C���h
	glBindVertexArray(vertexArray_);
	for (auto&& subset : subsets_) {
		// �}�e���A���̐ݒ�
		shader.material(materials_[subset.material]);
		// �|���S����`�悷��
		shader.begin();
		const GLushort* base = 0;
		glDrawElements(GL_TRIANGLES, subset.count, GL_UNSIGNED_SHORT, &base[subset.start]);
		shader.end();
	}
	glBindVertexArray(0);
}

// �t�@�C���̓ǂݍ���
void Mesh::Load(const std::string & file_name) {
	std::ifstream file(file_name, std::ios::binary);
	if (!file) {
		throw std::runtime_error("can not open " + file_name);
	}
	// ����
	Clear();
	// �}�e���A���̓ǂݍ���
	unsigned int material_size = 0;
	file.read((char*)&material_size, sizeof(material_size));
	materials_.resize(material_size);
	file.read((char*)materials_.data(), sizeof(Material) * material_size);
	// �T�u�Z�b�g�̓ǂݍ���
	unsigned int subset_size = 0;
	file.read((char*)&subset_size, sizeof(subset_size));
	subsets_.resize(subset_size);
	file.read((char*)subsets_.data(), sizeof(Subset) * subset_size);
	// ���_�C���f�b�N�X�̓ǂݍ���
	std::vector<GLushort> indices;
	unsigned int indices_size = 0;
	file.read((char*)&indices_size, sizeof(indices_size));
	indices.resize(indices_size);
	file.read((char*)indices.data(), sizeof(GLushort) * indices_size);
	// ���_�f�[�^�̓ǂݍ���
	std::vector<Vertex> vertices;
	unsigned int vertices_size = 0;
	file.read((char*)&vertices_size, sizeof(vertices_size));
	vertices.resize(vertices_size);
	file.read((char*)vertices.data(), sizeof(Vertex) * vertices_size);
	// �e�N�X�`���̍쐬
	std::experimental::filesystem::path mesh_path(file_name);
	std::string texture_path;
	if (mesh_path.has_parent_path()) {
		texture_path = mesh_path.parent_path().string() + "/";
	}
	for (auto& mat : materials_) {
		mat.texture = createTexture(texture_path + mat.texture_file_name);
		mat.normal_texture = createTexture(texture_path + mat.normal_texture_file_name);
	}
	// ���_�o�b�t�@�̍쐬
	vertices_ = createBuffer(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data());
	// �C���f�b�N�X�o�b�t�@�̍쐬
	indices_  = createBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), indices.data());
	// ���_�z��I�u�W�F�N�g�̍쐬
	vertexArray_ = createVertexArray();
}

// ����
void Mesh::Clear() {
	subsets_.clear();
	for (auto&& mat : materials_) {
		glDeleteTextures(1, &mat.texture);
	}
	materials_.clear();
	glDeleteVertexArrays(1, &vertexArray_);
	vertexArray_ = 0;
	glDeleteBuffers(1, &vertices_);
	vertices_ = 0;
	glDeleteBuffers(1, &indices_);
	indices_ = 0;
}

// �e�N�X�`���̓ǂݍ���
GLuint Mesh::createTexture(const std::string& file_name) {
	unsigned int width  = 0;
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

GLuint Mesh::createBuffer(GLenum target, GLuint size, const GLvoid* data) {
	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, GL_STATIC_DRAW);
	glBindBuffer(target, 0);
	return buffer;
}

GLuint Mesh::createVertexArray() {
	GLuint vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	// ���_���W�̃o�C���h
	glBindBuffer(GL_ARRAY_BUFFER, vertices_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bone_indices));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bone_weights));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, binormal));
	glEnableVertexAttribArray(6);
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_);
	glBindVertexArray(0);
	return vertexArray;
}

