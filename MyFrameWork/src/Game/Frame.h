#pragma once

#include "Device.h"

#include"Util/Time.h"

namespace boneLib {

	class Frame {
	protected:
		// �R���X�g���N�^
		Frame(int width = 640, int height = 480, bool fullScreen = false, float fps = 60.0f)
			: width_(width)
			, height_(height)
			, fullScreen_(fullScreen)
			, isRunnning_(true)
			, fps_(fps)
			, device_(width, height, fullScreen, fps) 
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// ���������[�N���o
		}

	public:
		// ���s
		int run() {
			// deltaTime ���Ǘ�����N���X�̏�����
			Time::Init();
			start();
			while (!device_.isClose() && isRunning()) {
			//while (isRunning()) {
				Time::Update();
				//update(60.0f / fps_);
				update(Time::DeltaTime());
				draw();
				device_.swap();
			}
			end();
			return 0;
		}

		void stopRunning() {
			isRunnning_ = false;
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
		// ���s����
		virtual bool isRunning() { return ((GetAsyncKeyState(VK_ESCAPE) == 0) && isRunnning_); }

	public:
		// �R�s�[�֎~
		Frame(const Frame& other) = delete;
		Frame& operator = (const Frame& other) = delete;

	private:
		// �E�B���h�E�̕�
		int width_;
		// �E�B���h�E�̍���
		int height_;
		// �t���X�N���[�����H
		bool fullScreen_;
		//���s�����H
		bool isRunnning_;
		// FPS
		float fps_;
		// GSLIB�f�o�C�X�N���X
		Device device_;
	};

}