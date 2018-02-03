#pragma once

#include "Window.h"

namespace bonelib {

	class Device {
	public:
		// コンストラクタ
		Device(int width, int height, bool fullScreen, float fps);
		// デストラクタ
		~Device();
		// バッファをスワップ
		void swap();
		// クローズするか？
		bool isClose();
	private:
		void initilaizeOpneGL();
		void activate(bool state);
		void resize(int width, int height);

		// コピー禁止
		Device(const Device& other) = delete;
		Device& operator = (const Device& other) = delete;
	public:
		// ウィンドウクラス
		Window mWindow;
		// フレームタイマ
		float mFrameTime;
		// 前フレームの時間
		float mPreviosTime;
	};
}