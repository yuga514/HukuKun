#include "GameScene.h"

// コンストラクタ
GameScene::GameScene()
{
}

// デストラクタ
GameScene::~GameScene()
{
	RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);
	for (int i = 0; i < 14; i++) {
		DeleteGraph(button[i]);
	}
	DeleteGraph(hand);
	DeleteGraph(title);
	DeleteGraph(background);
	DeleteGraph(ghost);
	DeleteGraph(okame);
	DeleteGraph(hyottoko);
	DeleteGraph(franken);
	DeleteGraph(clear);
	stageOne->~StageOne();
	stageTwo->~StageTwo();
	stageThree->~StageThree();
}

// 初期化
void GameScene::Initialize()
{
	// 画像などのリソースデータの読み込み
	font_path = "Resources/font/DFP勘亭流.ttf";
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	fontHandle = CreateFontToHandle("ＤＦＰ勘亭流", 64, 8);
	button[0] = LoadGraph("Resources/button/button1Black.png");
	button[1] = LoadGraph("Resources/button/button1.png");
	button[2] = LoadGraph("Resources/button/button2Black.png");
	button[3] = LoadGraph("Resources/button/button2.png");
	button[4] = LoadGraph("Resources/button/button3Black.png");
	button[5] = LoadGraph("Resources/button/button3.png");
	button[6] = LoadGraph("Resources/button/button4Black.png");
	button[7] = LoadGraph("Resources/button/button4.png");
	button[8] = LoadGraph("Resources/button/button5Black.png");
	button[9] = LoadGraph("Resources/button/button5.png");
	button[10] = LoadGraph("Resources/button/button6Black.png");
	button[11] = LoadGraph("Resources/button/button6.png");
	button[12] = LoadGraph("Resources/button/button7Black.png");
	button[13] = LoadGraph("Resources/button/button7.png");
	hand = LoadGraph("Resources/hand3.png");
	title = LoadGraph("Resources/title.png");
	background = LoadGraph("Resources/gamebackground.png");
	ghost = LoadGraph("Resources/ghost/ghost.png");
	okame = LoadGraph("Resources/okame/okame.png");
	hyottoko = LoadGraph("Resources/hyottoko/hyottoko.png");
	franken = LoadGraph("Resources/franken/franken.png");
	clear = LoadGraph("Resources/test.png");

	// ステージ1生成
	stageOne = new StageOne();
	stageOne->Initialize();
	// ステージ2生成
	stageTwo = new StageTwo();
	stageTwo->Initialize();
	// ステージ3生成
	stageThree = new StageThree();
	stageThree->Initialize();
	// ステージ4生成
	stageFour = new StageFour();
	stageFour->Initialize();
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
		if (ButtonCheck() == true) {
			if (ButtonCollision(0) == true) {
				scene = SAMPLE1;
			}
			if (ButtonCollision(2) == true) {
				scene = SELECT;
			}
		}
	}
	// 顔選択
	if (scene == SELECT) {

	}
	// サンプル1
	if (scene == SAMPLE1) {
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE1;
		}
	}
	// ステージ1
	if (scene == STAGE1) {
		if (ButtonCheck() == true && stageOne->GetAlpha() == 255) {
			if (ButtonCollision(2) && 50 <= stageOne->GetScore()) {
				scene = SAMPLE2;
			}
			if (ButtonCollision(3)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4)) {
				scene = SAMPLE1;
				stageOne->Reset();
			}
		}
		stageOne->Update();
	}
	// サンプル2
	if (scene == SAMPLE2) {
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE2;
		}
	}
	// ステージ2
	if (scene == STAGE2) {
		if (ButtonCheck() == true && stageTwo->GetAlpha() == 255) {
			if (ButtonCollision(2) && 60 <= stageTwo->GetScore()) {
				scene = SAMPLE3;
			}
			if (ButtonCollision(3)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4)) {
				scene = SAMPLE2;
				stageTwo->Reset();
			}
		}
		stageTwo->Update();
	}
	// サンプル3
	if (scene == SAMPLE3) {
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE3;
		}
	}
	// ステージ3
	if (scene == STAGE3) {
		if (ButtonCheck() == true && stageThree->GetAlpha() == 255) {
			if (ButtonCollision(2) && 70 <= stageThree->GetScore()) {
				scene = SAMPLE4;
			}
			if (ButtonCollision(3)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4)) {
				scene = SAMPLE3;
				stageThree->Reset();
			}
		}
		stageThree->Update();
	}
	// サンプル4
	if (scene == SAMPLE4) {
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE4;
		}
	}
	// ステージ4
	if (scene == STAGE4) {
		if (ButtonCheck() == true && stageFour->GetAlpha() == 255) {
			if (ButtonCollision(2) && 80 <= stageFour->GetScore()) {
				scene = CLEAR;
			}
			if (ButtonCollision(3)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4)) {
				scene = SAMPLE4;
				stageFour->Reset();
			}
		}
		stageFour->Update();
	}
	// クリア
	if (scene == CLEAR) {
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = TITLE;
			Reset();
		}
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
		if (ButtonCollision(0) == true) {
			DrawGraph(ButtonPosition[0].x, ButtonPosition[0].y, button[1], TRUE);
		}
		DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[4], TRUE);
		if (ButtonCollision(2) == true) {
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[5], TRUE);
		}
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
	}
	// 顔選択
	if (scene == SELECT) {
		DrawGraph(0, 0, background, TRUE);
	}
	// サンプル1
	if (scene == SAMPLE1) {
		SampleDraw(ghost, 50);
	}
	// ステージ1
	if (scene == STAGE1) {
		DrawGraph(0, 0, background, TRUE);
		stageOne->Draw();
		StageDraw(ghost, 50, stageOne->GetScore(), stageOne->GetAlpha());
	}
	// サンプル2
	if (scene == SAMPLE2) {
		SampleDraw(okame, 60);
	}
	// ステージ2
	if (scene == STAGE2) {
		DrawGraph(0, 0, background, TRUE);
		stageTwo->Draw();
		StageDraw(okame, 60, stageTwo->GetScore(), stageTwo->GetAlpha());
	}
	// サンプル3
	if (scene == SAMPLE3) {
		SampleDraw(hyottoko, 70);
	}
	// ステージ3
	if (scene == STAGE3) {
		DrawGraph(0, 0, background, TRUE);
		stageThree->Draw();
		StageDraw(hyottoko, 70, stageThree->GetScore(), stageThree->GetAlpha());
	}
	// サンプル4
	if (scene == SAMPLE4) {
		SampleDraw(franken, 80);
	}
	// ステージ4
	if (scene == STAGE4) {
		DrawGraph(0, 0, background, TRUE);
		stageFour->Draw();
		StageDraw(franken, 80, stageFour->GetScore(), stageFour->GetAlpha());
	}
	// クリア
	if (scene == CLEAR) {
		DrawGraph(0, 0, background, TRUE);
		DrawGraph(0, 0, clear, TRUE);
		DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[8], TRUE);
		if (ButtonCollision(2) == true) {
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[9], TRUE);
		}
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
	}
}

// サンプル表示の時に描画するもの
void GameScene::SampleDraw(int graphHandle, unsigned int norma)
{
	DrawGraph(0, 0, background, TRUE);
	DrawGraph(384, 104, graphHandle, TRUE);
	DrawFormatStringToHandle(350, 50, GetColor(0, 0, 0), fontHandle, "スコア%d以上でクリア", norma);
	DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[6], TRUE);
	if (ButtonCollision(2) == true) {
		DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[7], TRUE);
	}
	DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
}

// ステージ終了の時に描画するもの
void GameScene::StageDraw(int graphHandle, unsigned int norma, float score, unsigned int alpha)
{
	if (alpha == 255) {
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
			DrawGraph(384, 104, graphHandle, TRUE);
		}
		DrawFormatStringToHandle(500, 50, GetColor(0, 0, 0), fontHandle, "スコア:%d", (int)score);
		if (norma <= score) {
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[10], TRUE);
			if (ButtonCollision(2) == true) {
				DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[11], TRUE);
			}
		}
		DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[8], TRUE);
		if (ButtonCollision(3) == true) {
			DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[9], TRUE);
		}
		DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[12], TRUE);
		if (ButtonCollision(4) == true) {
			DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[13], TRUE);
		}
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
	}
}

// リセット
void GameScene::Reset()
{
	stageOne->Reset();
	stageTwo->Reset();
	stageThree->Reset();
	stageFour->Reset();
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