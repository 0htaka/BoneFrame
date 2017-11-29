// Animation.h
#ifndef ANIMATION_H_
#define	ANIMATION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

// �A�j���[�V�����N���X
class Animation {
public:
	struct KeyFrame {					// �L�[�t���[���\����
		float		frameNo;			// �t���[���ԍ�
		Vector3		scale;				// �g��k��
		Quaternion	rotate;				// ��]
		Vector3		position;			// ���s�ړ�
		Matrix		matrix() const;		// �ϊ��s����v�Z����
	};
public:
	// �R���X�g���N�^
	Animation();
	// �L�[�t���[���̎擾
	KeyFrame getKeyFrame(const std::string& boneName, float frameNo) const;
	// ����
	void clear();
	// �t�@�C������ǂݍ���
	void load(const std::string& fileName);
	// �I���t���[������Ԃ�
	float endFrame() const;
private:
	// �{�[���L�[�t���[��
	std::unordered_map<std::string, std::vector<KeyFrame>> boneKeyFrames_;
};

#endif

