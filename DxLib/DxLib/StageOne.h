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
	XMINT2 PartsPosition[2] = { { 100,100 }, { 100,500 } };

	// 画像などのリソースデータの変数宣言
	int face = LoadGraph("Resources/sampleface2.png");
	int hand1 = LoadGraph("Resources/hand1.png");
	int hand2 = LoadGraph("Resources/hand2.png");
	int eye1 = LoadGraph("Resources/eye1.png");
	int eye2 = LoadGraph("Resources/eye2.png");
};