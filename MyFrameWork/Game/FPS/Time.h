#pragma once

#include<chrono>

//���m�X�e�[�g�̃t���[���Ǘ��N���X
class Time {
	using TimePoint = std::chrono::system_clock::time_point;
public:
	//������
	static void Init(int TargetFPS = 60);
	//�X�V
	static void Update();
	//�f�o�b�O�`��i�������j
	static void Draw();
	//�f���^�^�C���̎擾
	static float DeltaTime();
	//�]�莞�ԕ���ҋ@�i�]�莞�Ԃ������true�A�ݒ肳�ꂽFPS�𒴂��Ă��܂��Ă�����false�j�߂�l�𗘗p���ĕ`�揈�����J�b�g�����肵�Ă��������B
	static bool Wait();

private:
	static inline int GetNowEpochTime();
private:
	//�ڕW��FPS
	static int m_FPS;
	static float m_frameSkipBorderMS;
	//�O�t���[���Ƃ̍���
	static float m_DeltaTime;

	//���݂̃t���[���̊J�n����
	static int m_StartTime;
	//�O��̃t���[���̊J�n����
	static int m_PreTime;

	//FPS�̌v�Z�p�x�i�T���v�����O���[�g�j
	//static const int m_SampleRate;
	//static int m_Cnt;

	//FPS
	//static int m_NowFPS;
};