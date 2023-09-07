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

	// 当たり判定のテンプレート
	void CollisionTemplate(unsigned int number);

	// リセット
	void Reset();

	// ネクストシーンフラグの取得
	unsigned int GetNextSceneFlag() { return nextSceneFlag; }

private: // メンバ変数
	unsigned int alpha = 0;
	unsigned int score = 0;
	unsigned int number = 2;
	bool catchFlag[2] = {};
	bool drawFlag[2] = {};
	bool scoreFlag[2] = {};
	bool nextSceneFlag = 0;

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