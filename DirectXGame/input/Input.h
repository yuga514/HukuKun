#pragma once

#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>

// 入力
class Input
{
public:
	struct MouseMove {
		LONG lX;
		LONG lY;
		LONG lZ;
	};

	struct StickMove {
		LONG lX;
		LONG lY;
		LONG lZ;
	};

private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// 初期化
	bool Initialize(HINSTANCE hInstance, HWND hwnd);

	// 毎フレーム処理
	void Update();

	// キーの押下をチェック
	bool PushKey(BYTE keyNumber);

	// キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);

	// マウスの押下をチェック
	bool PushMouse(UINT mouseNumber);

	// マウスのトリガーをチェック
	bool TriggerMouse(UINT mouseNumber);

	// ボタンの押下をチェック
	bool PushButton(UINT buttonNumber);

	// ボタンのトリガーをチェック
	bool TriggerButton(UINT buttonNumber);

	// 十字キーの押下をチェック
	bool PushArrow(UINT arrowNumber);

	// 十字キーのトリガーをチェック
	bool TriggerArrow(UINT arrowNumber);

	// マウス移動量を取得
	MouseMove GetMouseMove();

	// スティック移動量を取得
	StickMove GetStickMove();

	// ジョイスティックのポインタを取得
	ComPtr<IDirectInputDevice8> GetDevJoyStick() { return devJoystick; }

private: // メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devKeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};
	ComPtr<IDirectInputDevice8> devJoystick;
	DIJOYSTATE2 joyState = {};
	DIJOYSTATE2 joyStatePre = {};
};