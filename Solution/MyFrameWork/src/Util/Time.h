#pragma once
#include<chrono>

//���m�X�e�[�g�̃t���[���Ǘ��N���X
class Time {
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Sec = std::chrono::duration<float>;
public:
	// ������ �A�b�v�f�[�g�J�n�O�ɍs���Ă��������B
	static void Init(int TargetFPS = 60);
	// �X�V
	static void Update();
	// update()�Ăяo������̎���
	static float TookSec();
	// �]�莞�ԕ���ҋ@�i�]�莞�Ԃ������true�A�ݒ肳�ꂽFPS�𒴂��Ă��܂��Ă�����false�j�߂�l�𗘗p���ĕ`�揈�����J�b�g�����肵�Ă��������B
	static bool Wait();

	// �f���^�^�C���̎擾
	static float DeltaSec();
	// FPS
	static int TargetFPS();
	static int CurrentFPS();
private:
	static TimePoint GetCurrentTime();
private:
	// �ڕW��FPS
	static int _targetFps;
	// �O�t���[���Ƃ̍���
	static float _deltaTime;

	// ���݂̃t���[���̊J�n����
	static TimePoint _startTime;
	// �O��̃t���[���̊J�n����
	static TimePoint _preTime;

	// wait����ۂ̗]�莞�Ԃ̃{�[�_�[
	static float _waitBorder;

	//FPS�̌v�Z�p�x�i�T���v�����O���[�g�j
	/*static const int _sampleRate;
	static unsigned int _cnt;*/
};