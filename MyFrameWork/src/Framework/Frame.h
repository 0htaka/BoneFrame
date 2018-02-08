#pragma once

#include "Util/Window/Device.h"
#include "Util/Time.h"
#include "Util/Input/Input.h"

namespace bonelib {

	class Frame {
	protected:
		// コンストラクタ
		Frame(int width = 640, int height = 480, bool fullScreen = false, float fps = 60.0f)
			: mWidth(width)
			, mHeight(height)
			, mFullScreen(fullScreen)
			, mIsRunning(true)
			, mFps(fps)
			, mDevice(width, height, fullScreen, fps) {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// メモリリーク検出
		}

	public:
		// 実行
		int run() {
			// deltaTime を管理するクラスの初期化
			Time::Init();
			start();
			while (!mDevice.isClose() && isRunning()) {
				Time::Update();
				Input::Ins().Update();
				//update(60.0f / fps_);
				update(Time::DeltaTime());
				draw();
				mDevice.swap();
			}
			end();
			return 0;
		}

		void stopRunning() {
			mIsRunning = false;
		}

	private:
		// 開始
		virtual void start() {}
		// 更新
		virtual void update(float time) {}
		// 描画
		virtual void draw() {}
		// 終了
		virtual void end() {}
		// 実行中か gslib's
		virtual bool isRunning() { return true; }

	public:
		// コピー禁止
		Frame(const Frame& other) = delete;
		Frame& operator = (const Frame& other) = delete;

	private:
		// ウィンドウの幅
		int mWidth;
		// ウィンドウの高さ
		int mHeight;
		// フルスクリーンか？
		bool mFullScreen;
		//実行中か？
		bool mIsRunning;
		// FPS
		float mFps;
	public:
		// GSLIBデバイスクラス
		Device mDevice;
	};

}