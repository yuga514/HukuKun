#include "StageOne.h"

// コンストラクタ
StageOne::StageOne()
{
}

// デストラクタ
StageOne::~StageOne()
{
	DeleteGraph(plate);
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	for (int i = 0; i < partsNumber; i++) {
		DeleteGraph(parts[i]);
	}
}

// 初期化
void StageOne::Initialize()
{
	// 画像などのリソースデータの読み込み
	plate = LoadGraph("Resources/ghost/plate.png");
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	parts[0] = LoadGraph("Resources/ghost/LeftEye.png");
	parts[1] = LoadGraph("Resources/ghost/RightEye.png");
}

// 更新
void StageOne::Update()
{
	// マウス非表示
	SetMouseDispFlag(FALSE);

	// マウスの位置を取得
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	// 当たり判定
	Collision();

	// スコア加算
	ScoreAddition();

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		if (alpha < 255) {
			alpha += 3;
		}
	}
}

// 描画
void StageOne::Draw()
{
	// 顔
	DrawGraph(PlatePosition.x, PlatePosition.y, plate, TRUE);

	// 目
	if (drawFlag[0] == 0) {
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, parts[0], TRUE);
	}
	if (drawFlag[1] == 0) {
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, parts[1], TRUE);
	}

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, parts[0], TRUE);
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, parts[1], TRUE);
	}

	// 手
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
	}

	// スコア
	DrawFormatString(0, 0, GetColor(0, 0, 0), "スコア:%d", score);
}

// 当たり判定
void StageOne::Collision()
{
	// 左目
	CollisionTemplate(0);
	// 右目
	CollisionTemplate(1);
}

// スコア加算
void StageOne::ScoreAddition()
{
	// 左目
	ScoreAdditionTemplate(0);
	// 右目
	ScoreAdditionTemplate(1);
}

// 当たり判定のテンプレート
void StageOne::CollisionTemplate(unsigned int number)
{
	// 顔にパーツを置いていないとき、当たり判定が作動
	if (drawFlag[number] == 0) {
		// マウスをクリックしていないとき、パーツを離す
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = 0;
		}
		// パーツとマウスの当たり判定
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
				catchFlag[number] = 1;
			}
		}
		// パーツを掴んでいるとき、マウスに追尾する
		if (catchFlag[number] == 1) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// 顔とパーツの当たり判定
		if (PlatePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < PlatePosition.x + 512 &&
			PlatePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < PlatePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = 1;
			}
		}
	}
}

// スコア加算のテンプレート
void StageOne::ScoreAdditionTemplate(unsigned int number)
{
	// 顔にパーツを置いたら、スコアを判定する
	if (scoreFlag[number] == 0 && drawFlag[number] == 1) {
		if (PerfectPartsPosition[number].x - judge[0] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[0] &&
			PerfectPartsPosition[number].y - judge[0] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[0]) {
			score += 50;
		}
		else if (PerfectPartsPosition[number].x - judge[1] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[1] &&
			PerfectPartsPosition[number].y - judge[1] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[1]) {
			score += 40;
		}
		else if (PerfectPartsPosition[number].x - judge[2] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[2] &&
			PerfectPartsPosition[number].y - judge[2] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[2]) {
			score += 30;
		}
		else if (PerfectPartsPosition[number].x - judge[3] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[3] &&
			PerfectPartsPosition[number].y - judge[3] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[3]) {
			score += 20;
		}
		else if (PerfectPartsPosition[number].x - judge[4] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[4] &&
			PerfectPartsPosition[number].y - judge[4] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[4]) {
			score += 10;
		}
		scoreFlag[number] = 1;
	}
}

// リセット
void StageOne::Reset()
{
	score = 0;
	alpha = 0;	
	for (int i = 0; i < partsNumber; i++) {
		catchFlag[i] = 0;
		drawFlag[i] = 0;
		scoreFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}