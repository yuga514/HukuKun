#pragma once

#include <DirectXMath.h>

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "DebugCamera.h"

// ゲームシーン
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数
	// コンストクラタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	// 毎フレーム処理
	void Update();

	// 描画
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	// ゲームシーン用
	char str[100] = { 0 };
	unsigned int scene = 0;
	bool handFlag = 0;
	const float displacement = 10.0f;

	POINT handPoint = {};

	Sprite* title = nullptr;
	Sprite* background = nullptr;
	Sprite* hand1 = nullptr;
	Sprite* hand2 = nullptr;
};