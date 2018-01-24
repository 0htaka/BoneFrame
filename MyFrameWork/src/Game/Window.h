#pragma once

#include	<dsound.h>
#include	<GL/glut.h>
#include	<opengl_ext.h>

///////////////////


#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <functional>
#include <string>

#pragma comment(linker, "/entry:mainCRTStartup")

namespace boneLib {

	class Window {
	public:
		// コンストラクタ
		Window(int width, int height, const std::string& name, bool fullScreen);
		// デストラクタ
		~Window() {
			// ウィンドウの後処理
			glfwTerminate();
		}
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
		HWND getHWND() const;
		// タイマの取得
		float getTime() const;
	private:
		static void forcusCallback(GLFWwindow* window, int focused);
		static void resizeCallback(GLFWwindow* window, int width, int height);
	private:
		// GLFWのウィンドウ
		GLFWwindow* mWindow;
		// アクティブになった時の処理
		std::function<void(bool)> mForcusCallback;
		// サイズ変更時の処理
		std::function<void(int, int)> mResizeCallback;
		// クローズ時の処理
		std::function<void(void)> mCloseCallback;
	};

}