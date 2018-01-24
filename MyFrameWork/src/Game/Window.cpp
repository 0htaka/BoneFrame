#include "Window.h"

using namespace boneLib;

// コンストラクタ

Window::Window(int width, int height, const std::string & name, bool fullScreen) : mWindow(NULL) {
	if (!glfwInit()) {
		throw std::runtime_error("error glfwInit");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	//フルスクリーンにするかどうか
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;
	mWindow = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
	if (!mWindow) {
		glfwTerminate();
		throw std::runtime_error("error glfwCreateWindow");
	}
	glfwMakeContextCurrent(mWindow);
	// 自身をWindowとして設定（glfwGetWindowUserPointer()で取得できるようにするだけ？
	glfwSetWindowUserPointer(mWindow, this);
}

// ウィンドウを閉じたか？

bool  Window::isClose() const {
	return glfwWindowShouldClose(mWindow) != 0;
}

// ダブルバッファの交換

void  Window::swapBuffers() {
	glfwSwapBuffers(mWindow);
}

// イベントのポーリング

void  Window::pollEvents() {
	glfwPollEvents();
}

// スワップインターバルの設定

void  Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

// フォーカス時のコールバックを設定

void  Window::registerForcusCallback(std::function<void(bool)> fn) {
	mForcusCallback = fn;
	glfwSetWindowFocusCallback(mWindow, &forcusCallback);
}

// リサイズ時のコールバックを設定

void  Window::registerResizeCallback(std::function<void(int, int)> fn) {
	mResizeCallback = fn;
	glfwSetWindowSizeCallback(mWindow, &resizeCallback);
}

// ウィンドウハンドラの取得

HWND  Window::getHWND() const {
	return glfwGetWin32Window(mWindow);
}

// タイマの取得

float  Window::getTime() const {
	return (float)glfwGetTime();
}

void  Window::forcusCallback(GLFWwindow * window, int focused) {
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	self->mForcusCallback(focused == GL_TRUE);
}

void  Window::resizeCallback(GLFWwindow * window, int width, int height) {
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	self->mResizeCallback(width, height);
}
