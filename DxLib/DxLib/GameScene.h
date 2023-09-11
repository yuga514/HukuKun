#pragma once

#include "StageOne.h"
#include "StageTwo.h"

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

	const XMINT2 ButtonPosition[4] = { { 512,360 }, { 512,606 }, { 100,606 }, { 924,606 } };
	XMINT2 ClickPosition = {};
	XMINT2 MousePosition = {};

	StageOne* stageOne = nullptr;
	StageTwo* stageTwo = nullptr;

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
	};

	int fontHandle = CreateFontToHandle("HG行書体", 64, 8);

	// 画像などのリソースデータの変数宣言
	int button[5] = {};
	int hand = 0;
	int title = 0;
	int background = 0;
	int ghost = 0;
	int okame = 0;
	int hyottoko = 0;
	int franken = 0;
};