#include"Input.h"

const short STICKEXCURSION = 30000; //スティックの値の最大値
const short TRIGGEREXCURSION = 255; //トリガーの値の最大値
const double LIMIT = 0.2;  //傾きの補正の無効範囲

Input::Input()
{
	//PadInitialize();
	RegistFunc();
}

Input::~Input() {
}

Input & Input::Ins() {
	static Input instance;
	return instance;
}

void Input::RegistFunc() {
	//シャットダウン
	commandFunc[(int)Command::ShutDown]
		= [&](void)->bool
	{
		return (mKeys.IsKeyDown(VK_ESCAPE));
	};

	//スティック操作
	commandFunc[(int)Command::Up] = [this]() {return mKeys.GetKeyState(VK_UP); };
	commandFunc[(int)Command::Down] = [this]() {return mKeys.GetKeyState(VK_DOWN); };
	commandFunc[(int)Command::Left] = [this]() {return mKeys.GetKeyState(VK_LEFT); };
	commandFunc[(int)Command::Right] = [this]() {return mKeys.GetKeyState(VK_RIGHT); };
}

bool Input::GetCommand(Command command)
{
	return commandFunc[static_cast<int>(command)]();
}

void Input::Update() {
	mKeys.Update();

	/*ゲームパッド*/
	//pState = cInput;
	//GetJoypadXInputState(DX_INPUT_PAD1, &cInput);
	//pStick = cStick;
	////パッドのスティック情報初期化
	//GetJoypadXInputState(DX_INPUT_PAD1, &cStick);
	////パッドトリガー更新
	//is_P_LeftTrigger = is_C_LeftTrigger;
	//is_P_RightTrigger = is_C_RightTrigger;
	//is_C_LeftTrigger = GetLRTrigger().x >= 0.5f;
	//is_C_RightTrigger = GetLRTrigger().y >= 0.5f;
}

///*　ゲームパッド関係　*/
//bool Input::ConnectGamePad() {
//	bool padNum = (bool)GetJoypadNum();
//	return padNum;
//}
//void Input::PadInitialize() {
//	int padNum = GetJoypadNum();
//	if (padNum == 0) return;
//	//パッド1の接続設定 初期化
//	GetJoypadXInputState(DX_INPUT_PAD1, &cInput);
//}
//bool Input::IsGamePadUp(int pad) {
//	bool padState = false;
//	if (!cInput.Buttons[pad] && pState.Buttons[pad])
//		padState = true;
//
//	return padState;
//}
//
//bool Input::IsGamePadDown(int pad) {
//	bool padState = false;
//	if (cInput.Buttons[pad] && !pState.Buttons[pad])
//		padState = true;
//
//	return padState;
//}
//
//bool Input::IsGamePadState(int pad) {
//	bool padState = false;
//	if (cInput.Buttons[pad])
//		padState = true;
//
//	return padState;
//}
//
//
//Vector2 Input::GetWASDVelocity() {
//	//プレイヤーの移動量
//	Vector2 velocity = Vector2(0.0f, 0.0f);
//
//	if (IsKeyBoardState(KEY_INPUT_W))
//		velocity.y = 1.0f;
//	if (IsKeyBoardState(KEY_INPUT_A))
//		velocity.x = -1.0f;
//	if (IsKeyBoardState(KEY_INPUT_S))
//		velocity.y = -1.0f;
//	if (IsKeyBoardState(KEY_INPUT_D))
//		velocity.x = 1.0f;
//
//	//斜めの正規化
//	if (velocity.Length() != 0.0f)
//		velocity.Normalize();
//
//	return velocity;
//}
//
//
//Vector2 Input::GetULDRVelocity() {
//	//プレイヤーの移動量
//	Vector2 velocity = Vector2(0.0f, 0.0f);
//
//	if (IsKeyBoardState(KEY_INPUT_UP))
//		velocity.y = 1.0f;
//	if (IsKeyBoardState(KEY_INPUT_LEFT))
//		velocity.x = -1.0f;
//	if (IsKeyBoardState(KEY_INPUT_DOWN))
//		velocity.y = -1.0f;
//	if (IsKeyBoardState(KEY_INPUT_RIGHT))
//		velocity.x = 1.0f;
//
//	//斜めの正規化
//	if (velocity.Length() != 0.0f)
//		velocity.Normalize();
//
//	return velocity;
//}
//
//Vector2 Input::GetDPadVelocity() {
//	//プレイヤーの移動量
//	Vector2 velocity = Vector2();
//
//	if (IsGamePadState(XINPUT_BUTTON_DPAD_UP))
//		velocity.y = 1.0f;
//	if (IsGamePadState(XINPUT_BUTTON_DPAD_LEFT))
//		velocity.x = -1.0f;
//	if (IsGamePadState(XINPUT_BUTTON_DPAD_DOWN))
//		velocity.y = -1.0f;
//	if (IsGamePadState(XINPUT_BUTTON_DPAD_RIGHT))
//		velocity.x = 1.0f;
//
//	//斜めの正規化
//	if (velocity.Length() != 0.0f)
//		velocity.Normalize();
//
//	return velocity;
//}
//
//bool Input::IsAnyCommand()
//{
//	for (int i = 0; i < (int)Command::Max_Of_Num; i++)
//	{
//		if (GetCommand((Command)i))
//			return true;
//	}
//	return false;
//}
//
//float Input::JoyStickLimit(int target, double zone) {
//	int limit = (int)(STICKEXCURSION * zone);
//
//	if ((-limit <= target) && (target <= limit))
//		target = 0;
//
//	return (float)target;
//}
//
//Vector2 Input::GetLeftStick() {
//	int xAxis, yAxis; //軸の値保管
//
//	Vector2 velocity = Vector2();
//
//	xAxis = Mathf::Clamp(cStick.ThumbLX, -STICKEXCURSION, STICKEXCURSION);  //左スティックのx軸の値の補正
//	yAxis = Mathf::Clamp(cStick.ThumbLY, -STICKEXCURSION, STICKEXCURSION);  //左スティックのy軸の値の補正
//
//	xAxis = JoyStickLimit(xAxis, LIMIT);   //x軸の微妙な傾きの補正
//	yAxis = JoyStickLimit(yAxis, LIMIT);   //y軸の微妙な傾きの補正
//
//										   /* 各軸の値を1.0f以下に補正してvelocity化 */
//	velocity = Vector2(xAxis / STICKEXCURSION, yAxis / STICKEXCURSION);
//	return velocity;
//}
//
//Vector2 Input::GetLeftStick(XINPUT_STATE stick)
//{
//	float xAxis, yAxis; //軸の値保管
//
//	Vector2 velocity = Vector2();
//
//	xAxis = Mathf::Clamp(stick.ThumbLX, -STICKEXCURSION, STICKEXCURSION);  //左スティックのx軸の値の補正
//	yAxis = Mathf::Clamp(stick.ThumbLY, -STICKEXCURSION, STICKEXCURSION);  //左スティックのy軸の値の補正
//
//	xAxis = JoyStickLimit(xAxis, LIMIT);   //x軸の微妙な傾きの補正
//	yAxis = JoyStickLimit(yAxis, LIMIT);   //y軸の微妙な傾きの補正
//
//										   /* 各軸の値を1.0f以下に補正してvelocity化 */
//	velocity = Vector2(xAxis / STICKEXCURSION, yAxis / STICKEXCURSION);
//	return velocity;
//}
//
//Vector2 Input::GetRightStick() {
//	float xAxis, yAxis; //軸の値保管
//
//	Vector2 velocity = Vector2();
//
//	xAxis = Mathf::Clamp(cStick.ThumbRX, -STICKEXCURSION, STICKEXCURSION);  //右スティックのx軸の値の補正
//	yAxis = Mathf::Clamp(cStick.ThumbRY, -STICKEXCURSION, STICKEXCURSION);  //右スティックのy軸の値の補正
//
//	xAxis = JoyStickLimit(xAxis, LIMIT);   //x軸の微妙な傾きの補正
//	yAxis = JoyStickLimit(yAxis, LIMIT);   //y軸の微妙な傾きの補正
//
//										   /* 各軸の値を1.0f以下に補正してvelocity化 */
//	velocity = Vector2(xAxis / STICKEXCURSION, yAxis / STICKEXCURSION);
//	return velocity;
//}
//
//bool Input::GetLeftStickTrigger(MenuStickDirection direction)
//{
//	if (ConnectGamePad())
//	{
//		switch (direction)
//		{
//		case MenuStickDirection::DOWN:
//			if ((GetLeftStick(cStick).y <= -0.2f) && (GetLeftStick(pStick).y > -0.2f))
//				return true;
//			break;
//		case MenuStickDirection::UP:
//			if ((GetLeftStick(cStick).y >= 0.2f) && (GetLeftStick(pStick).y < 0.2f))
//				return true;
//			break;
//		case MenuStickDirection::LEFT:
//			if ((GetLeftStick(cStick).x <= -0.2f) && (GetLeftStick(pStick).x > -0.2f))
//				return true;
//			break;
//		case MenuStickDirection::RIGHT:
//			if ((GetLeftStick(cStick).x >= 0.2f) && (GetLeftStick(pStick).x < 0.2f))
//				return true;
//			break;
//		}
//	}
//	else
//	{
//		switch (direction)
//		{
//		case MenuStickDirection::DOWN:
//			if (IsKeyBoardDown(KEY_INPUT_S))
//				return true;
//			break;
//		case MenuStickDirection::UP:
//			if (IsKeyBoardDown(KEY_INPUT_W))
//				return true;
//			break;
//		case MenuStickDirection::LEFT:
//			if (IsKeyBoardDown(KEY_INPUT_A))
//				return true;
//			break;
//		case MenuStickDirection::RIGHT:
//			if (IsKeyBoardDown(KEY_INPUT_D))
//				return true;
//			break;
//		}
//	}
//	return false;
//}
//
//
//Vector2 Input::GetLRTrigger() {
//	float lTrigger, rTrigger; //トリガーの値保管
//
//	Vector2 trigger = Vector2(0.0f, 0.0f);
//	lTrigger = cStick.LeftTrigger;  //左トリガーの値
//	rTrigger = cStick.RightTrigger; //右トリガーの値
//								   /* 各トリガーの値を1.0f以下に補正 */
//	trigger = Vector2(lTrigger / TRIGGEREXCURSION, rTrigger / TRIGGEREXCURSION);
//	return trigger;
//}
//
//bool Input::IsDwonLTrigger()
//{
//	return is_C_LeftTrigger && !is_P_LeftTrigger;
//}
//
//bool Input::IsDwonRTrigger()
//{
//	return is_C_RightTrigger && !is_P_RightTrigger;
//}
//
//bool Input::IsUpLTrigger()
//{
//	return !is_C_LeftTrigger && is_P_LeftTrigger;
//}
//
//bool Input::IsUpRTrigger()
//{
//	return !is_C_RightTrigger && is_P_RightTrigger;
//}