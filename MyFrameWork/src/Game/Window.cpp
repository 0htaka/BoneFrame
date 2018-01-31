#include "Window.h"
#include <string>

// win32を使用、windows用(wgl)の関数を使用
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

using namespace bonelib;

GLFWwindow* Window::sMainWindow = NULL;
GLFWwindow* Window::sSubWindow = NULL;

#include <iostream>
void errorCallBack(int error, const char* description) {
	using namespace std;
	cout << "error code=" << error << " description:" << description << endl;
	throw runtime_error("GLFW error");
}

// コンストラクタ

Window::Window(int width, int height, const std::string & name, bool fullScreen)
{	
	//エラーコールバック設定
	glfwSetErrorCallback(errorCallBack);//glfwInit()する前に書いておく！
	if (!glfwInit()) {
		throw std::runtime_error("error glfwInit");
	}	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//サブウィンド作成
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	sSubWindow = glfwCreateWindow(1, 1, "subWin", NULL, NULL);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	//フルスクリーンにするかどうか
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;	
	sMainWindow = glfwCreateWindow(width, height, name.c_str(), monitor, sSubWindow);

	if (!sMainWindow) {
		glfwTerminate();
		throw std::runtime_error("error glfwCreateWindow");
	}

	glfwMakeContextCurrent(sMainWindow);
	// 自身をWindowとして設定（glfwGetWindowUserPointer()で取得できるようにするだけ？
	glfwSetWindowUserPointer(sMainWindow, this);
	//if(!glew)
}

// デストラクタ

Window::~Window() {
	// ウィンドウの後処理
	glfwTerminate();
}

// ウィンドウを閉じたか？

bool Window::isClose() const {
	return glfwWindowShouldClose(sMainWindow) != 0;
}

// ダブルバッファの交換

void Window::swapBuffers() {
	glfwSwapBuffers(sMainWindow);
}

// イベントのポーリング

void Window::pollEvents() {
	glfwPollEvents();
}

// スワップインターバルの設定

void Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

// フォーカス時のコールバックを設定

void Window::registerForcusCallback(std::function<void(bool)> fn) {
	mForcusCallback = fn;
	glfwSetWindowFocusCallback(sMainWindow, &forcusCallback);
}

// リサイズ時のコールバックを設定

void Window::registerResizeCallback(std::function<void(int, int)> fn) {
	mResizeCallback = fn;
	glfwSetWindowSizeCallback(sMainWindow, &resizeCallback);
}

// ウィンドウハンドラの取得

//HWND Window::getHWND() const {
//	return glfwGetWin32Window(sMainWindow);
//}

// タイマの取得

float Window::getTime() const {
	return (float)glfwGetTime();
}

void Window::forcusCallback(GLFWwindow * window, int focused) {
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	self->mForcusCallback(focused == GL_TRUE);
}

void Window::resizeCallback(GLFWwindow * window, int width, int height) {
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	self->mResizeCallback(width, height);
}


/*テスト用*/
GLFWwindow * bonelib::Window::createSubWin()
{
	GLFWwindow* win;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	win = glfwCreateWindow(1, 1, "SubWin", NULL, sMainWindow);
	if (!win)
		throw std::runtime_error("don't create opengl sub window");
	return win;
}