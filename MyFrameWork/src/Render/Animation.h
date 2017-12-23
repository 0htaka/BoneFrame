// Animation.h
#ifndef ANIMATION_H_
#define	ANIMATION_H_

#include"AssetManager/Base/ILoadable.h"

#include <vector>
#include <unordered_map>
#include <string>
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

// �A�j���[�V�����N���X
class Animation : public ILoadable {
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
	KeyFrame GetKeyFrame(const std::string& boneName, float frameNo) const;
	// ����
	void Clear();
	// �t�@�C������ǂݍ���
	void Load(const std::string& fileName) override;
	// �I���t���[������Ԃ�
	float EndFrame() const;
private:
	// �{�[���L�[�t���[��
	std::unordered_map<std::string, std::vector<KeyFrame>> boneKeyFrames_;
};

#endif

