#include "Skeleton.h"
#include "Animation.h"
#include <fstream>

Skeleton::Skeleton() {
}

std::size_t Skeleton::size() const {
	return bones_.size();
}

void Skeleton::calculateLocalMatrices(const Animation & animation, float frameNo, Matrix local[]) const {
	for (const auto& bone : bones_) {
		local[bone.ID] = animation.getKeyFrame(bone.name, frameNo).matrix();
	}
}

void Skeleton::calculateWorldMatrices(const Matrix& parent, const Matrix local[], Matrix world[]) const {
	world[0] = local[0] * bones_[0].transform * parent;
	for (int i = 1; i < (int)bones_.size(); ++i) {
		// ���[���h�ϊ� = ���[�J���ϊ� * �{�[���ϊ� * �e���[���h�ϊ�
		world[i] = local[i] * bones_[i].transform * world[bones_[i].parentID];
	}
}

void Skeleton::calculateSkinnedMatrices(const Matrix world[], Matrix skinned[]) const {
	for (const auto& bone : bones_) {
		// �X�L�j���O�s�� = �{�[���̋t�s�� * ���[���h�ϊ��s��
		skinned[bone.ID] = bone.inverse * world[bone.ID];
	}
}

// ����
void Skeleton::clear() {
	bones_.clear();
}

// �t�@�C���̓ǂݍ���
void Skeleton::load(const std::string & fileName) 
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		throw std::runtime_error("can not open " + fileName);
	}
	clear();
	unsigned int skeleton_size = 0;
	file.read((char*)&skeleton_size, sizeof(skeleton_size));
	bones_.resize(skeleton_size);
	file.read((char*)bones_.data(), sizeof(Bone) * skeleton_size);
}
