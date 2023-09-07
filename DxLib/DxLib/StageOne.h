#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageOne
{
public: // メンバ関数
	// コンストラクタ
	StageOne();

	// デストラクタ
	~StageOne();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 当たり判定
	void Collision();

	// リセット
	void Reset();

private: // メンバ変数
	bool catchFlag[2] = {};

	XMINT2 MousePosition = {};
	XMINT2 FacePosition = { 384,104 };
	XMINT2 PartsPosition[2] = { { 100,100 }, { 100,500 } };

	// 画像などのリソースデータの変数宣言
	int face = 0;
	int hand1 = 0;
	int hand2 = 0;
	int eye1 = 0;
	int eye2 = 0;
};