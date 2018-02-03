#include "Device.h"

#include <GL/glut.h>
#include <opengl_ext.h>

using namespace bonelib;

// �R���X�g���N�^
Device::Device(int width, int height, bool fullScreen, float fps) :
	mWindow(width, height, "Game Window", fullScreen),
	mFrameTime(1.0f / fps),
	mPreviosTime(mWindow.getTime()) {
	// �E�B���h�E�T�C�Y�ύX
	resize(width, height);
	// �E�B���h�E�T�C�Y�ύX���̊֐���ݒ�
	mWindow.registerResizeCallback([=](int w, int h) { resize(w, h); });
	// �E�B���h�E�A�N�e�B�u���̊֐���ݒ�
	mWindow.registerForcusCallback([=](bool flag) { activate(flag); });
	// �u����������L���ɂ���
	mWindow.swapInterval(1);
	// �n�������f�k�̏�����
	initilaizeOpneGL();
}

// �f�X�g���N�^

Device::~Device() {
	/* gslib's */
	//// �O���t�B�b�N�X�V�X�e���̏I������
	//gsFinishGraphics();
	//// ���̓f�o�C�X�V�X�e���̏I������
	//gsFinishInput();
	//// �T�E���h�V�X�e���̏I������
	//gsFinishSound();
}

// �o�b�t�@���X���b�v

void Device::swap() {
	mWindow.swapBuffers();
	mWindow.pollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	while ((mWindow.getTime() - mPreviosTime) < mFrameTime);
	mPreviosTime = mWindow.getTime();
}

// �N���[�Y���邩�H

bool Device::isClose() {
	return mWindow.isClose();
}

void Device::initilaizeOpneGL() {
	//�g���֐�������
	initialize_opengl_ext();
	// �ʃJ�����O�̏�����L���ɂ���
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// �f�v�X�o�b�t�@��1.0�ŃN���A����
	glClearDepth(1.0);
	// �e�v�X�e�X�g��L���ɂ���
	glEnable(GL_DEPTH_TEST);
	// �p�[�X�y�N�e�B�u�␳���s��
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// �u�����h��L��
	glEnable(GL_BLEND);
	// �f�t�H���g�̃u�����h����ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// �A���t�@�e�X�g��L��
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	// �X�y�L�����̌v�Z�𕪗�
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	// �f�t�H���g�̎��_�ϊ��̕ϊ��s���ݒ肷��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0f, 0.0f, 40.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
	// �f�t�H���g�̃��C�g�̐ݒ�
	static const float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const float lightSpeclar[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const float lightPosition[] = { 100.0f, 100.0f, 100.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpeclar);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	// ��ʏ���
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Device::activate(bool state) {
	/* gslib's */
	//// ���̓f�o�C�X�V�X�e���ɃA�N�e�B�u��Ԃ�`����
	//gsActivateInput(state ? GS_TRUE : GS_FALSE);
	//// �T�E���h�V�X�e���ɃA�N�e�B�u��Ԃ�`����
	//gsActivateSound(state ? GS_TRUE : GS_FALSE);
}

void Device::resize(int width, int height) {
	// �������O�ɂȂ�Ȃ��悤�ɒ���
	height = (height == 0) ? 1 : height;
	// �r���[�|�[�g�̐ݒ�
	glViewport(0, 0, width, height);
	// �����ˉe�̕ϊ��s���ݒ肷��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		45.0f,
		(float)width / (float)height,
		0.3f,
		1000.0f
	);
	// ���f���r���[���[�h�ɂ���
	glMatrixMode(GL_MODELVIEW);
}
