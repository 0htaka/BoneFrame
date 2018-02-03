#include "Device.h"

#include <GL/glut.h>
#include <opengl_ext.h>

using namespace bonelib;

// コンストラクタ
Device::Device(int width, int height, bool fullScreen, float fps) :
	mWindow(width, height, "Game Window", fullScreen),
	mFrameTime(1.0f / fps),
	mPreviosTime(mWindow.getTime()) {
	// ウィンドウサイズ変更
	resize(width, height);
	// ウィンドウサイズ変更時の関数を設定
	mWindow.registerResizeCallback([=](int w, int h) { resize(w, h); });
	// ウィンドウアクティブ時の関数を設定
	mWindow.registerForcusCallback([=](bool flag) { activate(flag); });
	// Ｖｓｙｎｃを有効にする
	mWindow.swapInterval(1);
	// ＯｐｅｎＧＬの初期化
	initilaizeOpneGL();
}

// デストラクタ

Device::~Device() {
	/* gslib's */
	//// グラフィックスシステムの終了処理
	//gsFinishGraphics();
	//// 入力デバイスシステムの終了処理
	//gsFinishInput();
	//// サウンドシステムの終了処理
	//gsFinishSound();
}

// バッファをスワップ

void Device::swap() {
	mWindow.swapBuffers();
	mWindow.pollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	while ((mWindow.getTime() - mPreviosTime) < mFrameTime);
	mPreviosTime = mWindow.getTime();
}

// クローズするか？

bool Device::isClose() {
	return mWindow.isClose();
}

void Device::initilaizeOpneGL() {
	//拡張関数初期化
	initialize_opengl_ext();
	// 面カリングの処理を有効にする
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// デプスバッファを1.0でクリアする
	glClearDepth(1.0);
	// テプステストを有効にする
	glEnable(GL_DEPTH_TEST);
	// パースペクティブ補正を行う
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// ブレンドを有効
	glEnable(GL_BLEND);
	// デフォルトのブレンド式を設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// アルファテストを有効
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	// スペキュラの計算を分離
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	// デフォルトの視点変換の変換行列を設定する
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0f, 0.0f, 40.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
	// デフォルトのライトの設定
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
	// 画面消去
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Device::activate(bool state) {
	/* gslib's */
	//// 入力デバイスシステムにアクティブ状態を伝える
	//gsActivateInput(state ? GS_TRUE : GS_FALSE);
	//// サウンドシステムにアクティブ状態を伝える
	//gsActivateSound(state ? GS_TRUE : GS_FALSE);
}

void Device::resize(int width, int height) {
	// 高さが０にならないように調整
	height = (height == 0) ? 1 : height;
	// ビューポートの設定
	glViewport(0, 0, width, height);
	// 透視射影の変換行列を設定する
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		45.0f,
		(float)width / (float)height,
		0.3f,
		1000.0f
	);
	// モデルビューモードにする
	glMatrixMode(GL_MODELVIEW);
}
