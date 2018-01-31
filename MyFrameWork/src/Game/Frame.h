#pragma once

#include "Device.h"

#include"Util/Time.h"

namespace bonelib {

	class Frame {
	protected:
		// �R���X�g���N�^
		Frame(int width = 640, int height = 480, bool fullScreen = false, float fps = 60.0f)
			: mWidth(width)
			, mHeight(height)
			, mFullScreen(fullScreen)
			, mIsRunning(true)
			, mFps(fps)
			, mDevice(width, height, fullScreen, fps) 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// ���������[�N���o
		}

	public:
		// ���s
		int run() {
			// deltaTime ���Ǘ�����N���X�̏�����
			Time::Init();
			start();
			while (!mDevice.isClose() && isRunning()) {
			//while (isRunning()) {
				Time::Update();
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
		// �J�n
		virtual void start() {}
		// �X�V
		virtual void update(float time) { (void)time; }
		// �`��
		virtual void draw() {}
		// �I��
		virtual void end() {}
		// ���s���� gslib's
		virtual bool isRunning() { return true; }

	public:
		// �R�s�[�֎~
		Frame(const Frame& other) = delete;
		Frame& operator = (const Frame& other) = delete;

	private:
		// �E�B���h�E�̕�
		int mWidth;
		// �E�B���h�E�̍���
		int mHeight;
		// �t���X�N���[�����H
		bool mFullScreen;
		//���s�����H
		bool mIsRunning;
		// FPS
		float mFps;
	public:
		// GSLIB�f�o�C�X�N���X
		Device mDevice;
	};

}