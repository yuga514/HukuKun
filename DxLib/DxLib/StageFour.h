#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageFour
{
public: // メンバ関数
	// コンストラクタ
	StageFour();

	// デストラクタ
	~StageFour();

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
	const int partsNumber = 10;
	float score = 0;
	unsigned int alpha = 0;
	bool catchFlag[10] = {};
	bool drawFlag[10] = {};
	bool scoreFlag[10] = {};

	const XMINT2 PerfectPartsPosition[10] = { { 502,300 }, { 650,300 }, { 575,434 }, { 464,198 }, { 687,182 },
												{ 567,373 }, { 496,247 }, { 648,240 }, { 377,158 }, { 787,158 } };
	const XMINT2 DefaultPartsPosition[10] = { { 100,100 }, { 100,300 }, { 100,500 }, { 200,200 }, { 200,400 },
												{ 952,100 }, { 952,300 }, { 952,500 }, { 1052,200 }, { 1052,400 } };
	XMINT2 PartsPosition[10] = { { 50,50 }, { 50,250 }, { 50,450 }, { 150,150 }, { 150,350 },
									{ 1002,50 }, { 1002,250 }, { 1002,450 }, { 1102,150 }, { 1102,350 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// 画像などのリソースデータの変数宣言
	int hand1 = 0;
	int hand2 = 0;
	int plate = 0;
	int parts[10] = {};
};