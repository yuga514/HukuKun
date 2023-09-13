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

	// サウンド
	void Sound();

	// 遊び方説明の時の当たり判定
	void RuleCollision(unsigned int scene1, unsigned int scene2);

	// 顔選択の時の当たり判定
	void SelectCollision(unsigned int scene1, unsigned int scene2, unsigned int scene3, bool selectFlag);

	// 遊び方説明の時に描画するもの
	void RuleDraw(int graphHandle);

	// 顔選択の時に描画するもの
	void SelectDraw(int graphHandle1, int graphHandle2, bool selectFlag);

	// サンプル表示の時に描画するもの
	void SampleDraw(int graphHandle, unsigned int norma);

	// ステージ終了の時に描画するもの
	void StageDraw(int graphHandle, unsigned int norma, float score, unsigned int alpha);

	// 遊び方説明の時に再生するもの
	void RuleSound();

	// 顔選択の時に再生するもの
	void SelectSound(bool selectFlag);

	// サンプル表示の時に再生するもの
	void SampleSound();

	// ステージ終了の時に再生するもの
	void StageSound(unsigned int norma, float score, unsigned int alpha);

	// リセット
	void Reset();

	// ボタンを押したかをチェック
	bool ButtonCheck();

	// ボタンの当たり判定
	bool ButtonCollision(unsigned int number);

private: // メンバ変数
	int buttonLog = 0;
	unsigned int scene = 0;
	bool SEflag = true;
	bool clearSEflag = true;

	const XMINT2 ButtonPosition[5] = { { 512,350 }, { 512,478 }, { 512,606 }, { 100,606 }, { 924,606 } };
	XMINT2 ClickPosition = {};
	XMINT2 MousePosition = {};

	StageOne* stageOne = nullptr;
	StageTwo* stageTwo = nullptr;
	StageThree* stageThree = nullptr;
	StageFour* stageFour = nullptr;

	enum sceneName
	{
		TITLE,
		RULE1,
		RULE2,
		RULE3,
		RULE4,
		SELECT1,
		SELECT2,
		SELECT3,
		SELECT4,
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

	// リソースデータの変数宣言
	LPCSTR font_path = 0;
	int fontHandle = 0;
	int button[16] = {};
	int rule[4] = {};
	int hand = 0;
	int title = 0;
	int background = 0;
	int clear = 0;
	int ghost = 0;
	int okame[2] = {};
	int hyottoko[2] = {};
	int franken[2] = {};
	int titleBGM = 0;
	int kuonBGM = 0;
	int buttonSE = 0;
	int hajimeSE = 0;
	int successSE = 0;
	int failedSE = 0;
	int clearSE = 0;
};