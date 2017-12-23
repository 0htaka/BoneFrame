#pragma once

#include<array>
#include<functional>
#include"Math/MathHelper.h"
#include"Math/Vector2.h"
#include"KeyInput\KeyInput.h"
#include<Windows.h>
//ゲームパッドの入力マックス
const int Max_Of_Num = 256;

//#ifdef __DXLIB
//#include<DxLib.h>
//#else
//#include<Xinput.h>
//#endif // __DXLIB


enum class Command
{
	ShutDown,//ゲーム終了
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

	/*　ゲームパッド関係*/
	//bool ConnectGamePad(); //パッドが接続されているか返す
	//void PadInitialize();
	//bool IsGamePadUp(int key);    //ゲームパッド UP
	//bool IsGamePadDown(int key);  //ゲームパッド DOWN
	//bool IsGamePadState(int key); //ゲームパッド STATE
	//
	//Vector2 GetDPadVelocity(); //移動量取得(DPAD版)
	//
	//float JoyStickLimit(int target, double zone = 0.2); //与えられた値を制限する
	//Vector2 GetLRTrigger();  //ゲームパッド Trigger(x Left,y Right)
	//bool IsDwonLTrigger();
	//bool IsDwonRTrigger();
	//bool IsUpLTrigger();
	//bool IsUpRTrigger();
	//
	//Vector2 GetLeftStick();  //ゲームパッド LeftStick(x xAxis,y null,z yAxis)
	//Vector2 GetLeftStick(XINPUT_STATE stick);
	//Vector2 GetRightStick(); //ゲームパッド RightStick(x xAxis,y null,z yAxis)
	//bool GetLeftStickTrigger(MenuStickDirection direction);	
public:
	/* キーボード関係 　*/
	KeyInput mKeys;
	
	/* ゲームパッド関係 */
	//XINPUT_STATE cInput;   //キーの現在の押下状況保存
	//XINPUT_STATE pState;   //キーの1F前の押下状況保存
	//					   //スティックのステイト情報
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