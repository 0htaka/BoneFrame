#include "KeyInput.h"
#include<Windows.h>
#include<WinUser.h> // �L�[�R�[�h���ڂ��Ă���

KeyInput::KeyInput()
{
}

void KeyInput::Update() {
	mPreKeys.swap(mCurKeys);
	GetKeyboardState(mCurKeys.data());
}

bool KeyInput::IsKeyUp(const int key) const
{
	return !GetKeyState(key) && PreKeyState(key);
}

bool KeyInput::IsKeyDown(const int key) const
{
	return GetKeyState(key) & !PreKeyState(key);
}

bool KeyInput::GetKeyState(const int key) const
{
	//�ŏ�ʃr�b�g��������Ă����Ԃ�\���i�ŉ��ʃr�b�g���g�O����ԁiCapsLock�Ȃǁj
	return mCurKeys[key] & 0x80;
}

#include<vector>
bool KeyInput::IsAnyKeyState() const
{
	for (size_t i = 0; i < Max_Key_Num;	i++)
	{
		if (mCurKeys[i] != mPreKeys[i])
			return true;
	}
	return false;
}

bool KeyInput::PreKeyState(const int key) const {
	return mPreKeys[key] & 0x80;
}
