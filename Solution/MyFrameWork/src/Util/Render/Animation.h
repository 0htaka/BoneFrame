// Animation.h
#ifndef ANIMATION_H_
#define	ANIMATION_H_

#include"Util/Load/ILoadable.h"

#include <vector>
#include <unordered_map>
#include <string>
#include "Util/Math/Matrix.h"
#include "Util/Math/Vector3.h"
#include "Util/Math/Quaternion.h"

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
	Animation(const std::string& filePath);
	void Update(float deltaSec);
	// �L�[�t���[���̎擾
	KeyFrame GetKeyFrame(const std::string& boneName, float frameNo) const;	
	// ����
	void Clear();
	// �t�@�C������ǂݍ���
	void Load(const std::string& fileName);
	// �I���t���[������Ԃ�
	float EndTime() const;
	//�Đ��ʒu
	float CurrentTime() const;
private:
	// �{�[���L�[�t���[��
	std::unordered_map<std::string, std::vector<KeyFrame>> mBoneKeyFrames;
	//�A�j���[�V�����̃T���v����
	int FPS{ 60 };
	//�A�j���[�V�����t���[����
	float mFrameNum{ 0 };
	//�A�j���[�V�����^�C�}
	float mPlayTimer{ 0 };
};

#endif

