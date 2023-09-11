﻿#include "GameScene.h"

// コンストラクタ
GameScene::GameScene()
{
}

// デストラクタ
GameScene::~GameScene()
{
	for (int i = 0; i < 5; i++) {
		DeleteGraph(button[i]);
	}
	DeleteGraph(hand);
	DeleteGraph(title);
	DeleteGraph(background);
	DeleteGraph(ghost);
	DeleteGraph(okame);
	stageOne->~StageOne();
	stageTwo->~StageTwo();
}

// 初期化
void GameScene::Initialize()
{
	// 画像などのリソースデータの読み込み
	button[0] = LoadGraph("Resources/button/button4.png");
	button[1] = LoadGraph("Resources/button/button5.png");
	button[2] = LoadGraph("Resources/button/button.png");
	button[3] = LoadGraph("Resources/button/button2.png");
	button[4] = LoadGraph("Resources/button/button3.png");
	hand = LoadGraph("Resources/hand3.png");
	title = LoadGraph("Resources/title.png");
	background = LoadGraph("Resources/test2.png");
	ghost = LoadGraph("Resources/ghost/ghost.png");
	okame = LoadGraph("Resources/okame/okame.png");
	hyottoko = LoadGraph("Resources/hyottoko/hyottoko.png");
	franken = LoadGraph("Resources/franken/franken.png");

	// ステージ1生成
	stageOne = new StageOne();
	stageOne->Initialize();
	// ステージ2生成
	stageTwo = new StageTwo();
	stageTwo->Initialize();
}

// 更新
void GameScene::Update()
{
	// マウス非表示
	SetMouseDispFlag(FALSE);

	// マウスの位置を取得
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	// タイトル
	if (scene == TITLE) {
		if (ButtonCheck() == true && ButtonCollision(0) == true) {
			scene = SAMPLE1;
		}
	}
	// サンプル1
	if (scene == SAMPLE1) {
		if (ButtonCheck() == true && ButtonCollision(1) == true) {
			scene = STAGE1;
		}
	}
	// ステージ1
	if (scene == STAGE1) {
		if (ButtonCheck() == true && stageOne->GetAlpha() == 255) {
			if (ButtonCollision(1) && 50 <= stageOne->GetScore()) {
				scene = SAMPLE2;
			}
			if (ButtonCollision(2)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(3)) {
				scene = SAMPLE1;
				stageOne->Reset();
			}
		}
		stageOne->Update();
	}
	// サンプル2
	if (scene == SAMPLE2) {
		if (ButtonCheck() == true && ButtonCollision(1) == true) {
			scene = STAGE2;
		}
	}
	// ステージ2
	if (scene == STAGE2) {
		if (ButtonCheck() == true && stageTwo->GetAlpha() == 255) {
			if (ButtonCollision(1) && 60 <= stageTwo->GetScore()) {
				scene = SAMPLE3;
			}
			if (ButtonCollision(2)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(3)) {
				scene = SAMPLE2;
				stageTwo->Reset();
			}
		}
		stageTwo->Update();
	}
}

// 描画
void GameScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// タイトル
	if (scene == TITLE) {
		DrawGraph(0, 0, title, TRUE);
		DrawGraph(ButtonPosition[0].x, ButtonPosition[0].y, button[0], TRUE);
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
	}
	// サンプル1
	if (scene == SAMPLE1) {
		DrawGraph(0, 0, background, TRUE);
		DrawGraph(384, 104, ghost, TRUE);
		SampleDraw();
		// スコア50以上でクリア
		DrawFormatString(0, 0, GetColor(0, 0, 0), "スコア50以上でクリア");
	}
	// ステージ1
	if (scene == STAGE1) {
		DrawGraph(0, 0, background, TRUE);
		stageOne->Draw();
		if (stageOne->GetAlpha() == 255) {
			if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
				DrawGraph(384, 104, ghost, TRUE);
			}
			if (50 < stageOne->GetScore()) {
				DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[3], TRUE);
			}
			StageDraw();
		}
	}
	// サンプル2
	if (scene == SAMPLE2) {
		DrawGraph(0, 0, background, TRUE);
		DrawGraph(384, 104, okame, TRUE);
		SampleDraw();
		// スコア60以上でクリア
		DrawFormatString(0, 0, GetColor(0, 0, 0), "スコア60以上でクリア");
	}
	// ステージ2
	if (scene == STAGE2) {
		DrawGraph(0, 0, background, TRUE);
		stageTwo->Draw();
		if (stageTwo->GetAlpha() == 255) {
			if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
				DrawGraph(384, 104, okame, TRUE);
			}
			if (60 < stageTwo->GetScore()) {
				DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[3], TRUE);
			}
			StageDraw();
		}
	}
}

// ステージ終了の時に共通して描画するもの
void GameScene::StageDraw()
{
	DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[2], TRUE);
	DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[4], TRUE);
	DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
}

// サンプル表示の時に共通して描画するもの
void GameScene::SampleDraw()
{
	DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[1], TRUE);
	DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
}

// リセット
void GameScene::Reset()
{
	stageOne->Reset();
	stageTwo->Reset();
}

// ボタンを押したかをチェック
bool GameScene::ButtonCheck()
{
	if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 && (buttonLog & MOUSE_INPUT_LEFT) != 0) {
		return true;
	}
	else {
		return false;
	}
}

// ボタンの当たり判定
bool GameScene::ButtonCollision(unsigned int number)
{
	if (ButtonPosition[number].x < MousePosition.x && MousePosition.x < ButtonPosition[number].x + 256 &&
		ButtonPosition[number].y < MousePosition.y && MousePosition.y < ButtonPosition[number].y + 64) {
		return true;
	}
	else {
		return false;
	}
}