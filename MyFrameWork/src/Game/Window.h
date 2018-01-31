#pragma once

#include <functional>

#pragma comment(linker, "/entry:mainCRTStartup")

struct GLFWwindow;

namespace bonelib {

	class Window {
	public:
		// �R���X�g���N�^
		Window(int width, int height, const std::string& name, bool fullScreen);
		// �f�X�g���N�^
		~Window();
		// �E�B���h�E��������H
		bool isClose() const;
		// �_�u���o�b�t�@�̌���
		void swapBuffers();
		// �C�x���g�̃|�[�����O
		void pollEvents();
		// �X���b�v�C���^�[�o���̐ݒ�
		void swapInterval(int interval);
		// �t�H�[�J�X���̃R�[���o�b�N��ݒ�
		void registerForcusCallback(std::function<void(bool)> fn);
		// ���T�C�Y���̃R�[���o�b�N��ݒ�
		void registerResizeCallback(std::function<void(int, int)> fn);
		// �E�B���h�E�n���h���̎擾
		//HWND getHWND() const;
		// �^�C�}�̎擾
		float getTime() const;
	public://�T�u�X���b�h�e�X�g�p�@�����o		
		static GLFWwindow* createSubWin();
		static GLFWwindow* sSubWindow;
	private:
		static void forcusCallback(GLFWwindow* window, int focused);
		static void resizeCallback(GLFWwindow* window, int width, int height);
	public:
		// GLFW�̃E�B���h�E
		static GLFWwindow* sMainWindow;
		// �A�N�e�B�u�ɂȂ������̏���
		std::function<void(bool)> mForcusCallback;
		// �T�C�Y�ύX���̏���
		std::function<void(int, int)> mResizeCallback;
		// �N���[�Y���̏���
		std::function<void(void)> mCloseCallback;
	};

}