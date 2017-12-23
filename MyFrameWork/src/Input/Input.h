#pragma once

#include<array>
#include<functional>
#include"Math/MathHelper.h"
#include"Math/Vector2.h"
#include"KeyInput\KeyInput.h"
#include<Windows.h>
//�Q�[���p�b�h�̓��̓}�b�N�X
const int Max_Of_Num = 256;

//#ifdef __DXLIB
//#include<DxLib.h>
//#else
//#include<Xinput.h>
//#endif // __DXLIB


enum class Command
{
	ShutDown,//�Q�[���I��
	Up,
	Down,
	Left,
	Right,
	Max_Of_Num
};

class Input {
private:
	Input();
	Input& operator =(Input& other) = delete;

private:
	~Input();
	void RegistFunc();
public:
	static Input& Ins();	

	void Update();
	bool GetCommand(Command command);

	/*�@�Q�[���p�b�h�֌W*/
	//bool ConnectGamePad(); //�p�b�h���ڑ�����Ă��邩�Ԃ�
	//void PadInitialize();
	//bool IsGamePadUp(int key);    //�Q�[���p�b�h UP
	//bool IsGamePadDown(int key);  //�Q�[���p�b�h DOWN
	//bool IsGamePadState(int key); //�Q�[���p�b�h STATE
	//
	//Vector2 GetDPadVelocity(); //�ړ��ʎ擾(DPAD��)
	//
	//float JoyStickLimit(int target, double zone = 0.2); //�^����ꂽ�l�𐧌�����
	//Vector2 GetLRTrigger();  //�Q�[���p�b�h Trigger(x Left,y Right)
	//bool IsDwonLTrigger();
	//bool IsDwonRTrigger();
	//bool IsUpLTrigger();
	//bool IsUpRTrigger();
	//
	//Vector2 GetLeftStick();  //�Q�[���p�b�h LeftStick(x xAxis,y null,z yAxis)
	//Vector2 GetLeftStick(XINPUT_STATE stick);
	//Vector2 GetRightStick(); //�Q�[���p�b�h RightStick(x xAxis,y null,z yAxis)
	//bool GetLeftStickTrigger(MenuStickDirection direction);	
public:
	/* �L�[�{�[�h�֌W �@*/
	KeyInput mKeys;
	
	/* �Q�[���p�b�h�֌W */
	//XINPUT_STATE cInput;   //�L�[�̌��݂̉����󋵕ۑ�
	//XINPUT_STATE pState;   //�L�[��1F�O�̉����󋵕ۑ�
	//					   //�X�e�B�b�N�̃X�e�C�g���
	//XINPUT_STATE cStick;
	//XINPUT_STATE pStick;
	//
	//bool is_C_LeftTrigger;
	//bool is_P_LeftTrigger;
	//bool is_C_RightTrigger;
	//bool is_P_RightTrigger;

	using CommandFunc = std::array < std::function<bool(void)>, static_cast<int>(Command::Max_Of_Num)>;
	CommandFunc commandFunc;
};