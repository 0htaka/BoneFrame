#pragma once

#include<chrono>

//モノステートのフレーム管理クラス
class Time {
	using TimePoint = std::chrono::system_clock::time_point;
public:
	//初期化
	static void Init(int TargetFPS = 60);
	//更新
	static void Update();
	//デバッグ描画（未実装）
	static void Draw();
	//デルタタイムの取得
	static float DeltaTime();
	//余剰時間分を待機（余剰時間があればtrue、設定されたFPSを超えてしまっていたらfalse）戻り値を利用して描画処理をカットしたりしてください。
	static bool Wait();
	//FPS
	static int TargetFPS();
private:
	static inline int GetNowEpochTime();
private:
	//目標のFPS
	static int mFPS;
	static float mFrameSkipBorderMS;
	//前フレームとの差分
	static float mDeltaTime;

	//現在のフレームの開始時間
	static int mStartTime;
	//前回のフレームの開始時間
	static int mPreTime;

	//FPSの計算頻度（サンプリングレート）
	//static const int m_SampleRate;
	//static int m_Cnt;

	//FPS
	//static int m_NowFPS;
};