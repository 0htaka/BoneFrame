#ifndef SKELETON_H_
#define SKELETON_H_

#include <string>
#include <vector>
#include "Math/Matrix.h"

class Animation;

class Skeleton {
public:
	struct Bone {
		char			name[32];	// �{�[����
		int				ID;			// �{�[��ID
		int				parentID;	// �e�{�[��ID
		Matrix			transform;	// �{�[���̕ϊ��s��
		Matrix			inverse;	// �{�[���̋t�s��
	};

public:
	// �R���X�g���N�^
	Skeleton();
	// �{�[������Ԃ�
	std::size_t size() const;
	// �{�[���̃��[�J���ϊ��s����v�Z����
	void calculateLocalMatrices(const Animation& animation, float frameNo, Matrix local[]) const;
	// �{�[���̃��[���h�ϊ��s����v�Z����
	void calculateWorldMatrices(const Matrix& parent, const Matrix local[], Matrix world[]) const;
	// �X�L�j���O�p�̕ϊ��s����v�Z����
	void calculateSkinnedMatrices(const Matrix world[], Matrix skinned[]) const;
	// ����
	void clear();
	// �t�@�C���ǂݍ���
	void load(const std::string& fileName);
private:
	// �{�[���z��
	std::vector<Bone>	bones_;
};

#endif
