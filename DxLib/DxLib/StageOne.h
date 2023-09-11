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
	unsigned int GetScore() { return score; }

	// アルファ値の取得
	unsigned int GetAlpha() { return alpha; }

private: // メンバ変数
	const int judge[5] = { 7,14,21,28,35 };
	const int partsNumber = 5;
	unsigned int score = 0;
	unsigned int alpha = 0;
	bool catchFlag[5] = {};
	bool drawFlag[5] = {};
	bool scoreFlag[5] = {};

	const XMINT2 PerfectPartsPosition[5] = { { 480,200 }, { 672,200 }, { 576,296 }, { 368,328 }, { 784,328 } };
	const XMINT2 DefaultPartsPosition[5] = { { 100,100 }, { 100,300 }, { 100,500 }, { 1052,200 }, { 1052,400 } };
	XMINT2 PartsPosition[5] = { { 100,100 }, { 100,300 }, { 100,500 }, { 1052,200 }, { 1052,400 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// 画像などのリソースデータの変数宣言
	int hand1 = 0;
	int hand2 = 0;
	int plate = 0;
	int parts[5] = {};
};