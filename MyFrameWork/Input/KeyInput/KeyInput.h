#pragma once

#include<array>

class KeyInput {
public:
	static const unsigned int Max_Key_Num = 256;
	using Keys = std::array<unsigned char, Max_Key_Num>;
public:
	KeyInput();
	void Update();
	bool IsKeyUp(const int key) const;
	bool IsKeyDown(const int key) const;
	bool GetKeyState(const int key) const;	
	bool PreKeyState(const int key) const;
	bool IsAnyKeyState() const;
private:
	/* �L�[�{�[�h�֌W �@*/
	Keys mCurKeys;   //�L�[�̌��݂̉����󋵕ۑ�
	Keys mPreKeys;   //�L�[��1F�O�̉����󋵕ۑ�
};

