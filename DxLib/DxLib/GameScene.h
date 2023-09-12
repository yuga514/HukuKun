#pragma once

#include "StageOne.h"
#include "StageTwo.h"
#include "StageThree.h"
#include "StageFour.h"

// ゲームシーン
class GameScene
{
public: // メンバ関数
	// コンストクラタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// サンプル表示の時に共通して描画するもの
	void SampleDraw();

	// ステージ終了の時に共通して描画するもの
	void StageDraw();

	// リセット
	void Reset();

	// ボタンを押したかをチェック
	bool ButtonCheck();

	// ボタンの当たり判定
	bool ButtonCollision(unsigned int number);

private: // メンバ変数
	int buttonLog = 0;
	unsigned int scene = 0;

	const XMINT2 ButtonPosition[7] = { { 512,360 }, { 512,606 }, { 100,606 }, { 924,606 } };
	XMINT2 ClickPosition = {};
	XMINT2 MousePosition = {};

	StageOne* stageOne = nullptr;
	StageTwo* stageTwo = nullptr;
	StageThree* stageThree = nullptr;
	StageFour* stageFour = nullptr;

	enum sceneName
	{
		TITLE,
		SAMPLE1,
		STAGE1,
		SAMPLE2,
		STAGE2,
		SAMPLE3,
		STAGE3,
		SAMPLE4,
		STAGE4,
		CLEAR
	};

	// 画像などのリソースデータの変数宣言
	int graphHandle[10];


	int button[7] = {};
	int hand = 0;
	int title = 0;
	int background = 0;
	int ghost = 0;
	int okame = 0;
	int hyottoko = 0;
	int franken = 0;
	int clear = 0;
};