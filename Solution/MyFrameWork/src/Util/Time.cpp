#include "Time.h"
#include<thread>
#include<cmath>

using namespace std::chrono;

int				Time::_targetFps = 60;
float			Time::_deltaTime = 0;
Time::TimePoint	Time::_startTime;
Time::TimePoint	Time::_preTime;
float			Time::_waitBorder = 0;

void Time::Init(int TargetFPS) {
	_targetFps = TargetFPS;
	_waitBorder = (1.f / _targetFps) / 500.f;

	_deltaTime = 1.0f / _targetFps;
	_startTime = GetCurrentTime();
	_preTime = _startTime;
}

void Time::Update() {
	//�����ɗv�������Ԃ��~���b�ɕϊ�
	_preTime = _startTime;
	_startTime = GetCurrentTime();

	_deltaTime = duration_cast<Sec>(_startTime - _preTime).count();
}

float Time::TookSec() {
	// update���Ă΂�Ă���̏��v����
	auto tookTime = GetCurrentTime() - _startTime;
	return duration_cast<Sec>(tookTime).count();
}

bool Time::Wait() {
	// �ڕWFPS�� deltaTime
	float targetDelta = 1.0f / _targetFps;
	float tookSec = TookSec();

	// �ڕW�Ƃ̍���
	float waitTime = targetDelta - tookSec;
	if (waitTime > _waitBorder) {
		//if (waitTime > 0) {
			// ���Ԃ��]���Ă���΃X���[�v
		std::this_thread::sleep_for(Sec(waitTime - _waitBorder));
		return true;
	}
	return false;
}

float Time::DeltaSec() {
	return _deltaTime;
}


int Time::TargetFPS() {
	return _targetFps;
}

int Time::CurrentFPS() {
	return _deltaTime > std::numeric_limits<float>::epsilon()
		? int(1 / _deltaTime)
		: TargetFPS();
}

Time::TimePoint Time::GetCurrentTime() {
	return Clock::now();
}
