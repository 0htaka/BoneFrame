#include "Window.h"

using namespace boneLib;

// �R���X�g���N�^

Window::Window(int width, int height, const std::string & name, bool fullScreen) : mWindow(NULL) {
	if (!glfwInit()) {
		throw std::runtime_error("error glfwInit");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	//�t���X�N���[���ɂ��邩�ǂ���
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;
	mWindow = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
	if (!mWindow) {
		glfwTerminate();
		throw std::runtime_error("error glfwCreateWindow");
	}
	glfwMakeContextCurrent(mWindow);
	// ���g��Window�Ƃ��Đݒ�iglfwGetWindowUserPointer()�Ŏ擾�ł���悤�ɂ��邾���H
	glfwSetWindowUserPointer(mWindow, this);
}

// �E�B���h�E��������H

bool  Window::isClose() const {
	return glfwWindowShouldClose(mWindow) != 0;
}

// �_�u���o�b�t�@�̌���

void  Window::swapBuffers() {
	glfwSwapBuffers(mWindow);
}

// �C�x���g�̃|�[�����O

void  Window::pollEvents() {
	glfwPollEvents();
}

// �X���b�v�C���^�[�o���̐ݒ�

void  Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

// �t�H�[�J�X���̃R�[���o�b�N��ݒ�

void  Window::registerForcusCallback(std::function<void(bool)> fn) {
	mForcusCallback = fn;
	glfwSetWindowFocusCallback(mWindow, &forcusCallback);
}

// ���T�C�Y���̃R�[���o�b�N��ݒ�

void  Window::registerResizeCallback(std::function<void(int, int)> fn) {
	mResizeCallback = fn;
	glfwSetWindowSizeCallback(mWindow, &resizeCallback);
}

// �E�B���h�E�n���h���̎擾

HWND  Window::getHWND() const {
	return glfwGetWin32Window(mWindow);
}

// �^�C�}�̎擾

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
