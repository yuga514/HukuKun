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

	// スコア加算
	void ScoreAddition();

	// 当たり判定のテンプレート
	void CollisionTemplate(unsigned int number);

	// スコア加算のテンプレート
	void ScoreAdditionTemplate(unsigned int number);

	// リセット
	void Reset();

	// スコアの取得
	unsigned int GetScore() { return score; }

	// アルファ値の取得
	unsigned int GetAlpha() { return alpha; }

private: // メンバ変数
	const unsigned int judge[5] = { 7,14,21,28,35 };
	const unsigned int parts = 2;
	unsigned int score = 0;
	unsigned int alpha = 0;
	bool catchFlag[2] = {};
	bool drawFlag[2] = {};
	bool scoreFlag[2] = {};

	const XMINT2 PerfectPartsPosition[2] = { { 480,200 }, { 672,200 } };
	XMINT2 PartsPosition[2] = { { 100,100 }, { 100,500 } };
	XMINT2 MousePosition = {};
	XMINT2 FacePosition = { 384,104 };

	// 画像などのリソースデータの変数宣言
	int face = 0;
	int hand1 = 0;
	int hand2 = 0;
	int eye1 = 0;
	int eye2 = 0;
};