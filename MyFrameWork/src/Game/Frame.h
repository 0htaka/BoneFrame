#pragma once

#include "Device.h"

#include"Util/Time.h"

namespace boneLib {

	class Frame {
	protected:
		// コンストラクタ
		Frame(int width = 640, int height = 480, bool fullScreen = false, float fps = 60.0f)
			: width_(width)
			, height_(height)
			, fullScreen_(fullScreen)
			, isRunnning_(true)
			, fps_(fps)
			, device_(width, height, fullScreen, fps) 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// メモリリーク検出
		}

	public:
		// 実行
		int run() {
			// deltaTime を管理するクラスの初期化
			Time::Init();
			start();
			while (!device_.isClose() && isRunning()) {
			//while (isRunning()) {
				Time::Update();
				//update(60.0f / fps_);
				update(Time::DeltaTime());
				draw();
				device_.swap();
			}
			end();
			return 0;
		}

		void stopRunning() {
			isRunnning_ = false;
		}

	private:
		// 開始
		virtual void start() {}
		// 更新
		virtual void update(float time) { (void)time; }
		// 描画
		virtual void draw() {}
		// 終了
		virtual void end() {}
		// 実行中か
		virtual bool isRunning() { return ((GetAsyncKeyState(VK_ESCAPE) == 0) && isRunnning_); }

	public:
		// コピー禁止
		Frame(const Frame& other) = delete;
		Frame& operator = (const Frame& other) = delete;

	private:
		// ウィンドウの幅
		int width_;
		// ウィンドウの高さ
		int height_;
		// フルスクリーンか？
		bool fullScreen_;
		//実行中か？
		bool isRunnning_;
		// FPS
		float fps_;
		// GSLIBデバイスクラス
		Device device_;
	};

}