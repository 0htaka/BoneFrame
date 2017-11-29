#include "Time.h"
#include<thread>
#include<cmath>

//#include<DxLib.h>

using namespace std;
using namespace chrono;

int				Time::m_FPS = 60;
float			Time::m_DeltaTime = 0;
int				Time::m_StartTime;
int				Time::m_PreTime;

void Time::Init(int TargetFPS)
{
	m_FPS = TargetFPS;

	m_StartTime = GetNowEpochTime();
	m_PreTime = m_StartTime;
}

void Time::Update()
{
	//処理に要した時間をミリ秒に変換
	m_PreTime = m_StartTime;
	m_StartTime = GetNowEpochTime();

	m_DeltaTime = (m_StartTime - m_PreTime) / 1000.0;
}

#include<gslib.h>
#include<string>
void Time::Draw()
{	
	string temp = std::to_string(m_DeltaTime) + "\n";
	//OutputDebugString(temp.c_str());
}

float Time::DeltaTime()
{
	return m_DeltaTime;
}

bool Time::Wait()
{
	//実際に処理にかかった時間
	auto tookTime = GetNowEpochTime() - m_StartTime;
	//目標FPS時の deltaTime を計算
	int targetDT = (int)std::ceilf(1000.0f / m_FPS);

	//目標との差分
	int waitTime = targetDT - tookTime;

	if (waitTime > (1.0f / m_FPS) * 1000) {
		//時間が余っていればスリープ
		this_thread::sleep_for(milliseconds(waitTime));
		/*DrawFormatString(0, 16, GetColor(255, 255, 255)
		, "waiteTime = %f"
		, waitTime / 1000.0f);*/
		return true;
	}
	return false;
}

inline int Time::GetNowEpochTime()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
