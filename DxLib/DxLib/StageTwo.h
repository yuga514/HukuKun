#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageTwo
{
public: // メンバ関数
	// コンストラクタ
	StageTwo();

	// デストラクタ
	~StageTwo();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 当たり判定
	void Collision(unsigned int number);

	// スコア加算
	void ScoreAddition(unsigned int number);

	// パーツ紛失
	void PartsLost(unsigned int number);

	// リセット
	void Reset();

	// パーツの当たり判定をチェック
	bool PartsCollisionCheck(unsigned int number, unsigned int number2);

	// パーツ持っているかをチェック
	bool CatchCheck();

	// パーツが全て並べられたかをチェック
	bool DrawCheck();

	// スコアの取得
	float GetScore() { return score; }

	// アルファ値の取得
	unsigned int GetAlpha() { return alpha; }

private: // メンバ変数
	const int judge[5] = { 7,14,21,28,35 };
	const int partsNumber = 8;
	float score = 0.0f;
	unsigned int alpha = 0;
	bool catchFlag[8] = {};
	bool drawFlag[8] = {};
	bool scoreFlag[8] = {};

	const XMINT2 PerfectPartsPosition[8] = { { 511,268 }, { 641,268 }, { 577,405 }, { 499,348 },
												{ 653,348 }, { 576,319 }, { 516,204 }, { 636,204 } };
	const XMINT2 DefaultPartsPosition[8] = { { 100,100 }, { 100,300 }, { 200,200 }, { 200,400 },
												{ 952,100 }, { 952,300 }, { 1052,200 }, { 1052,400 } };
	XMINT2 PartsPosition[8] = { { 100,100 }, { 100,300 }, { 200,200 }, { 200,400 },
								{ 952,100 }, { 952,300 }, { 1052,200 }, { 1052,400 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// 画像などのリソースデータの変数宣言
	int plate = 0;
	int hand1 = 0;
	int hand2 = 0;
	int parts[8] = {};
};