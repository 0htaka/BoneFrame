#pragma once

#include <functional>

#pragma comment(linker, "/entry:mainCRTStartup")

struct GLFWwindow;

namespace bonelib {

	class Window {
	public:
		// コンストラクタ
		Window(int width, int height, const std::string& name, bool fullScreen);
		// デストラクタ
		~Window();
		// ウィンドウを閉じたか？
		bool isClose() const;
		// ダブルバッファの交換
		void swapBuffers();
		// イベントのポーリング
		void pollEvents();
		// スワップインターバルの設定
		void swapInterval(int interval);
		// フォーカス時のコールバックを設定
		void registerForcusCallback(std::function<void(bool)> fn);
		// リサイズ時のコールバックを設定
		void registerResizeCallback(std::function<void(int, int)> fn);
		// ウィンドウハンドラの取得
		//HWND getHWND() const;
		// タイマの取得
		float getTime() const;
	public://サブスレッドテスト用　メンバ		
		static GLFWwindow* createSubWin();
		static GLFWwindow* sSubWindow;
	private:
		static void forcusCallback(GLFWwindow* window, int focused);
		static void resizeCallback(GLFWwindow* window, int width, int height);
	public:
		// GLFWのウィンドウ
		static GLFWwindow* sMainWindow;
		// アクティブになった時の処理
		std::function<void(bool)> mForcusCallback;
		// サイズ変更時の処理
		std::function<void(int, int)> mResizeCallback;
		// クローズ時の処理
		std::function<void(void)> mCloseCallback;
	};

}