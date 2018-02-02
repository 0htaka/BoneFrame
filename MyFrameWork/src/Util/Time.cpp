#include "Time.h"
#include<thread>
#include<cmath>

//#include<DxLib.h>

using namespace std;
using namespace chrono;

int				Time::mFPS = 60;
float			Time::mDeltaTime = 0;
int				Time::mStartTime;
int				Time::mPreTime;

void Time::Init(int TargetFPS)
{
	mFPS = TargetFPS;

	mStartTime = GetNowEpochTime();
	mPreTime = mStartTime;
}

void Time::Update()
{
	//�����ɗv�������Ԃ��~���b�ɕϊ�
	mPreTime = mStartTime;
	mStartTime = GetNowEpochTime();

	mDeltaTime = (mStartTime - mPreTime) / 1000.0f;
}

//#include<gslib.h>
#include<string>
void Time::Draw()
{	
	string temp = std::to_string(mDeltaTime) + "\n";
	//OutputDebugString(temp.c_str());
}

float Time::DeltaTime()
{
	return mDeltaTime;
}

bool Time::Wait()
{
	//���ۂɏ����ɂ�����������
	auto tookTime = GetNowEpochTime() - mStartTime;
	//�ڕWFPS���� deltaTime ���v�Z
	int targetDT = (int)std::ceilf(1000.0f / mFPS);

	//�ڕW�Ƃ̍���
	int waitTime = targetDT - tookTime;

	if (waitTime > (1.0f / mFPS) * 1000) {
		//���Ԃ��]���Ă���΃X���[�v
		this_thread::sleep_for(milliseconds(waitTime));
		/*DrawFormatString(0, 16, GetColor(255, 255, 255)
		, "waiteTime = %f"
		, waitTime / 1000.0f);*/
		return true;
	}
	return false;
}

int Time::TargetFPS()
{
	return mFPS;
}

inline int Time::GetNowEpochTime()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
