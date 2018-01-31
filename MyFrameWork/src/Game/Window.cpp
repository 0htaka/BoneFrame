#include "Window.h"
#include <string>

// win32���g�p�Awindows�p(wgl)�̊֐����g�p
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

// �R���X�g���N�^

Window::Window(int width, int height, const std::string & name, bool fullScreen)
{	
	//�G���[�R�[���o�b�N�ݒ�
	glfwSetErrorCallback(errorCallBack);//glfwInit()����O�ɏ����Ă����I
	if (!glfwInit()) {
		throw std::runtime_error("error glfwInit");
	}	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//�T�u�E�B���h�쐬
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	sSubWindow = glfwCreateWindow(1, 1, "subWin", NULL, NULL);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	//�t���X�N���[���ɂ��邩�ǂ���
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;	
	sMainWindow = glfwCreateWindow(width, height, name.c_str(), monitor, sSubWindow);

	if (!sMainWindow) {
		glfwTerminate();
		throw std::runtime_error("error glfwCreateWindow");
	}

	glfwMakeContextCurrent(sMainWindow);
	// ���g��Window�Ƃ��Đݒ�iglfwGetWindowUserPointer()�Ŏ擾�ł���悤�ɂ��邾���H
	glfwSetWindowUserPointer(sMainWindow, this);
	//if(!glew)
}

// �f�X�g���N�^

Window::~Window() {
	// �E�B���h�E�̌㏈��
	glfwTerminate();
}

// �E�B���h�E��������H

bool Window::isClose() const {
	return glfwWindowShouldClose(sMainWindow) != 0;
}

// �_�u���o�b�t�@�̌���

void Window::swapBuffers() {
	glfwSwapBuffers(sMainWindow);
}

// �C�x���g�̃|�[�����O

void Window::pollEvents() {
	glfwPollEvents();
}

// �X���b�v�C���^�[�o���̐ݒ�

void Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

// �t�H�[�J�X���̃R�[���o�b�N��ݒ�

void Window::registerForcusCallback(std::function<void(bool)> fn) {
	mForcusCallback = fn;
	glfwSetWindowFocusCallback(sMainWindow, &forcusCallback);
}

// ���T�C�Y���̃R�[���o�b�N��ݒ�

void Window::registerResizeCallback(std::function<void(int, int)> fn) {
	mResizeCallback = fn;
	glfwSetWindowSizeCallback(sMainWindow, &resizeCallback);
}

// �E�B���h�E�n���h���̎擾

//HWND Window::getHWND() const {
//	return glfwGetWin32Window(sMainWindow);
//}

// �^�C�}�̎擾

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


/*�e�X�g�p*/
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