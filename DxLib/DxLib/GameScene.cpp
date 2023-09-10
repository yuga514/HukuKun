#include "GameScene.h"

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

	// ステージ1生成
	stageOne = new StageOne();
	stageOne->Initialize();
}

// 更新
void GameScene::Update()
{
	// マウス非表示
	SetMouseDispFlag(FALSE);

	// マウスの位置を取得
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	if (scene == TITLE) {
		// 処理
	}
	if (scene == SAMPLE1) {
		// 処理
	}
	if (scene == STAGE1) {
		stageOne->Update();
	}
	if (scene == SAMPLE2) {
		// 処理
	}

	// シーン推移
	SceneChange();
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
		DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[1], TRUE);
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
		// スコア50以上でクリア
		DrawFormatString(0, 0, GetColor(0, 0, 0), "スコア50以上でクリア");
	}
	// ステージ1
	if (scene == STAGE1) {
		DrawGraph(0, 0, background, TRUE);
		stageOne->Draw();
		if (stageOne->GetAlpha() == 255) {
			if (50 < stageOne->GetScore()) {
				DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[3], TRUE);
			}
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[2], TRUE);
			DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[4], TRUE);
			DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
		}
	}
	// サンプル2
	if (scene == SAMPLE2) {
		DrawGraph(0, 0, background, TRUE);
		DrawGraph(384, 104, okame, TRUE);
	}
}

// シーン推移
void GameScene::SceneChange()
{
	// タイトル
	if (scene == TITLE) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(0) == true) {
			scene = SAMPLE1;
		}
	}
	// サンプル1
	if (scene == SAMPLE1) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(1) == true) {
			scene = STAGE1;
		}
	}
	// ステージ1
	if (scene == STAGE1) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && stageOne->GetAlpha() == 255) {
			if (ButtonCollision(1) && 50 <= stageOne->GetScore()) {
				scene = SAMPLE2;
			}
			if (ButtonCollision(2)) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(3)) {
				scene = SAMPLE1;
				Reset();
			}
		}
	}
}

// リセット
void GameScene::Reset()
{
	stageOne->Reset();
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