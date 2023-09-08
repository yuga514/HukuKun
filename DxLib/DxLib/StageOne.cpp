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
	parts[2] = LoadGraph("Resources/ghost/mouth.png");
	parts[3] = LoadGraph("Resources/ghost/LeftHand.png");
	parts[4] = LoadGraph("Resources/ghost/RightHand.png");
}

// 更新
void StageOne::Update()
{
	// マウス非表示
	SetMouseDispFlag(FALSE);

	// マウスの位置を取得
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	for (int i = 0; i < partsNumber; i++) {
		// 当たり判定
		Collision(i);
		// スコア加算
		ScoreAddition(i);
	}

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1 && drawFlag[2] == 1 && drawFlag[3] == 1 && drawFlag[4] == 1) {
		if (alpha < 255) {
			alpha += 3;
		}
	}
}

// 描画
void StageOne::Draw()
{
	// プレート
	DrawGraph(PlatePosition.x, PlatePosition.y, plate, TRUE);

	// パーツ
	for (int i = 0; i < partsNumber; i++) {
		if (drawFlag[i] == 0) {
			DrawGraph(PartsPosition[i].x, PartsPosition[i].y, parts[i], TRUE);
		}
	}

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1 && drawFlag[2] == 1 && drawFlag[3] == 1 && drawFlag[4] == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		for (int i = 0; i < partsNumber; i++) {
			if (drawFlag[i] == 1) {
				DrawGraph(PartsPosition[i].x, PartsPosition[i].y, parts[i], TRUE);
			}
		}
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
void StageOne::Collision(unsigned int number)
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

// スコア加算
void StageOne::ScoreAddition(unsigned int number)
{
	// 顔にパーツを置いたら、スコアを判定する
	if (scoreFlag[number] == 0 && drawFlag[number] == 1) {
		if (PerfectPartsPosition[number].x - judge[0] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[0] &&
			PerfectPartsPosition[number].y - judge[0] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[0]) {
			score += 20;
		}
		else if (PerfectPartsPosition[number].x - judge[1] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[1] &&
			PerfectPartsPosition[number].y - judge[1] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[1]) {
			score += 16;
		}
		else if (PerfectPartsPosition[number].x - judge[2] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[2] &&
			PerfectPartsPosition[number].y - judge[2] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[2]) {
			score += 12;
		}
		else if (PerfectPartsPosition[number].x - judge[3] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[3] &&
			PerfectPartsPosition[number].y - judge[3] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[3]) {
			score += 8;
		}
		else if (PerfectPartsPosition[number].x - judge[4] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[4] &&
			PerfectPartsPosition[number].y - judge[4] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[4]) {
			score += 4;
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
	PartsPosition[1] = { 100,300 };
	PartsPosition[2] = { 100,500 };
	PartsPosition[3] = { 1052,200 };
	PartsPosition[4] = { 1052,400 };
}