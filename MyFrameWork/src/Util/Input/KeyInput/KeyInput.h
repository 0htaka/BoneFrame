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
	/* キーボード関係 　*/
	Keys mCurKeys;   //キーの現在の押下状況保存
	Keys mPreKeys;   //キーの1F前の押下状況保存
};

