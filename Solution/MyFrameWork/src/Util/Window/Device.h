#pragma once

#include "Window.h"

namespace bonelib {

	class Device {
	public:
		// �R���X�g���N�^
		Device(int width, int height, bool fullScreen, float fps);
		// �f�X�g���N�^
		~Device();
		// �o�b�t�@���X���b�v
		void swap();
		// �N���[�Y���邩�H
		bool isClose();
	private:
		void initilaizeOpneGL();
		void activate(bool state);
		void resize(int width, int height);

		// �R�s�[�֎~
		Device(const Device& other) = delete;
		Device& operator = (const Device& other) = delete;
	public:
		// �E�B���h�E�N���X
		Window mWindow;
		// �t���[���^�C�}
		float mFrameTime;
		// �O�t���[���̎���
		float mPreviosTime;
	};
}