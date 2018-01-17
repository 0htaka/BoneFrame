#ifndef SKELETON_H_
#define SKELETON_H_

#include"Load\ILoadable.h"

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
	Skeleton(const std::string& filePath);
	// �{�[������Ԃ�
	std::size_t Size() const;
	// �{�[���̃��[�J���ϊ��s����v�Z����
	void CalculateLocalMatrices(const Animation& animation, float frameNo, Matrix local[]) const;
	// �{�[���̃��[���h�ϊ��s����v�Z����
	void CalculateWorldMatrices(const Matrix& parent, const Matrix local[], Matrix world[]) const;
	// �X�L�j���O�p�̕ϊ��s����v�Z����
	void CalculateSkinnedMatrices(const Matrix world[], Matrix skinned[]) const;
	// ����
	void Clear();
	// �t�@�C���ǂݍ���
	void Load(const std::string& fileName);
private:
	// �{�[���z��
	std::vector<Bone>	bones_;
};

#endif
