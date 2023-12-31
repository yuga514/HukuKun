#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageThree
{
public: // メンバ関数
	// コンストラクタ
	StageThree();

	// デストラクタ
	~StageThree();

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

	// セレクトフラグの取得
	bool GetSelectFlag() { return selectFlag; }

	// セレクトフラグの設定
	void SetSelectFlag() { selectFlag = true; }

private: // メンバ変数
	const int judge[5] = { 7,14,21,28,35 };
	const int partsNumber = 8;
	float score = 0.0f;
	unsigned int alpha = 0;
	bool selectFlag = false;
	bool catchFlag[8] = {};
	bool drawFlag[8] = {};
	bool scoreFlag[8] = {};

	const XMINT2 PerfectPartsPosition[8] = { { 519,230 }, { 632,230 }, { 548,408 }, { 473,336 },
												{ 679,336 }, { 576,319 }, { 471,186 }, { 680,186 } };
	const XMINT2 DefaultPartsPosition[8] = { { 50,50 }, { 50,250 }, { 150,150 }, { 150,350 },
												{ 1002,50 }, { 1002,250 }, { 1102,150 }, { 1102,350 } };
	XMINT2 PartsPosition[8] = { { 50,50 }, { 50,250 }, { 150,150 }, { 150,350 },
								{ 1002,50 }, { 1002,250 }, { 1102,150 }, { 1102,350 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// 画像などのリソースデータの変数宣言
	int hand1 = 0;
	int hand2 = 0;
	int plate = 0;
	int parts[8] = {};
};