#include "KeyInput.h"
#include<Windows.h>
#include<WinUser.h> // キーコードが載っている

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
	//最上位ビットが押されている状態を表す（最下位ビットがトグル状態（CapsLockなど）
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
