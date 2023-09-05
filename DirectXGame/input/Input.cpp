#include <cassert>

#include "Input.h"

#pragma comment(lib, "dinput8.lib")

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	// DirectInputオブジェクトの生成
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

	// キーボードデバイスの生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);

	// マウスデバイスの生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

	// ジョイスティックデバイスの生成
	result = dinput->CreateDevice(GUID_Joystick, &devJoystick, NULL);

	// 入力データ形式のセット
	result = devKeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式

	// 排他制御レベルのセット
	result = devKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	// 入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	if (devJoystick) {
		// 入力データ形式のセット
		result = devJoystick->SetDataFormat(&c_dfDIJoystick2); // 標準形式

		// 排他制御レベルのセット
		result = devJoystick->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}

	return true;
}

void Input::Update()
{
	HRESULT result;

	{ // キーボード
		result = devKeyboard->Acquire(); // キーボード動作開始

		// 前回のキー入力を保存
		memcpy(keyPre, key, sizeof(key));

		// キーの入力
		result = devKeyboard->GetDeviceState(sizeof(key), key);
	}

	{ // マウス
		result = devMouse->Acquire(); // マウス動作開始

		// 前回の入力を保存
		mouseStatePre = mouseState;

		// マウスの入力
		result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	}

	if (devJoystick) { // ジョイスティック
		result = devJoystick->Acquire(); // ジョイスティック動作開始

		// 前回の入力を保存
		joyStatePre = joyState;

		// ジョイスティックの入力
		result = devJoystick->GetDeviceState(sizeof(joyState), &joyState);
	}
}

bool Input::PushKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0でなければ押している
	if (key[keyNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0で、今回が0でなければトリガー
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::PushMouse(UINT mouseNumber)
{
	// 0でなければ押している
	if (mouseState.rgbButtons[mouseNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerMouse(UINT mouseNumber)
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[mouseNumber] && mouseState.rgbButtons[mouseNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::PushButton(UINT buttonNumber)
{
	// 0でなければ押している
	if (joyState.rgbButtons[buttonNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerButton(UINT buttonNumber)
{
	// 前回が0で、今回が0でなければトリガー
	if (!joyStatePre.rgbButtons[buttonNumber] && joyState.rgbButtons[buttonNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::PushArrow(UINT arrowNumber)
{
	// 0でなければ押している
	if (joyState.rgdwPOV[0] == arrowNumber * 4500) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerArrow(UINT arrowNumber)
{
	// 前回が0で、今回が0でなければトリガー
	if (!joyStatePre.rgdwPOV[0] && joyState.rgdwPOV[0] == arrowNumber * 4500) {
		return true;
	}

	// トリガーでない
	return false;
}

Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;
	return tmp;
}

Input::StickMove Input::GetStickMove()
{
	StickMove tmp;
	tmp.lX = joyState.lX;
	tmp.lY = joyState.lY;
	tmp.lZ = joyState.lZ;
	return tmp;
}