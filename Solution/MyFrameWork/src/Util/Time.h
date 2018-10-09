#pragma once
#include<chrono>

//モノステートのフレーム管理クラス
class Time {
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Sec = std::chrono::duration<float>;
public:
	// 初期化 アップデート開始前に行ってください。
	static void Init(int TargetFPS = 60);
	// 更新
	static void Update();
	// update()呼び出しからの時間
	static float TookSec();
	// 余剰時間分を待機（余剰時間があればtrue、設定されたFPSを超えてしまっていたらfalse）戻り値を利用して描画処理をカットしたりしてください。
	static bool Wait();

	// デルタタイムの取得
	static float DeltaSec();
	// FPS
	static int TargetFPS();
	static int CurrentFPS();
private:
	static TimePoint GetCurrentTime();
private:
	// 目標のFPS
	static int _targetFps;
	// 前フレームとの差分
	static float _deltaTime;

	// 現在のフレームの開始時間
	static TimePoint _startTime;
	// 前回のフレームの開始時間
	static TimePoint _preTime;

	// waitする際の余剰時間のボーダー
	static float _waitBorder;

	//FPSの計算頻度（サンプリングレート）
	/*static const int _sampleRate;
	static unsigned int _cnt;*/
};