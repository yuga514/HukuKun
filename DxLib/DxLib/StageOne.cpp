#include "StageOne.h"

// コンストラクタ
StageOne::StageOne()
{
}

// デストラクタ
StageOne::~StageOne()
{
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	DeleteGraph(plate);
	for (int i = 0; i < partsNumber; i++) {
		DeleteGraph(parts[i]);
	}
}

// 初期化
void StageOne::Initialize()
{
	// 画像などのリソースデータの読み込み
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	plate = LoadGraph("Resources/ghost/plate.png");
	parts[0] = LoadGraph("Resources/ghost/LeftEye.png");
	parts[1] = LoadGraph("Resources/ghost/RightEye.png");
	parts[2] = LoadGraph("Resources/ghost/mouth.png");
	parts[3] = LoadGraph("Resources/ghost/LeftHand.png");
	parts[4] = LoadGraph("Resources/ghost/RightHand.png");
}

// 更新
void StageOne::Update()
{
	// マウスの位置を取得
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	for (int i = 0; i < partsNumber; i++) {
		// 当たり判定
		Collision(i);
		// スコア加算
		ScoreAddition(i);
		// パーツ紛失
		PartsLost(i);
	}

	// 結果発表
	if (DrawCheck() == true && alpha < 255) {
		alpha += 3;
	}

#ifdef _DEBUG
	// チート
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
		for (int i = 0; i < partsNumber; i++) {
			PartsPosition[i] = PerfectPartsPosition[i];
		}
	}
#endif
}

// 描画
void StageOne::Draw()
{
	// プレート
	DrawGraph(PlatePosition.x, PlatePosition.y, plate, TRUE);

	// アルファブレンド
	if (DrawCheck() == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}

	// パーツ
	for (int i = 0; i < partsNumber; i++) {
		if (drawFlag[i] == false || DrawCheck() == true && alpha < 255 ||
			alpha == 255 && (GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) {
			DrawGraph(PartsPosition[i].x, PartsPosition[i].y, parts[i], TRUE);
		}
	}

	// 手
	if (alpha == 0) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
		}
	}
}

// 当たり判定
void StageOne::Collision(unsigned int number)
{
	// 顔にパーツを置いていないとき、当たり判定が作動
	if (drawFlag[number] == false) {
		// マウスをクリックしていないとき、パーツを離す
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = false;
		}
		// パーツとマウスの当たり判定
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && CatchCheck() == true) {
				catchFlag[number] = true;
			}
		}
		// パーツを掴んでいるとき、マウスに追尾する
		if (catchFlag[number] == true) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// 顔とパーツの当たり判定
		if (PlatePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < PlatePosition.x + 512 &&
			PlatePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < PlatePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = true;
			}
		}
	}
}

// スコア加算
void StageOne::ScoreAddition(unsigned int number)
{
	// 顔にパーツを置いたら、スコアを判定する
	if (scoreFlag[number] == false && drawFlag[number] == true) {
		if (PartsCollisionCheck(number, 0) == true) {
			score += 20.0f;
		}
		else if (PartsCollisionCheck(number, 1) == true) {
			score += 16.0f;
		}
		else if (PartsCollisionCheck(number, 2) == true) {
			score += 12.0f;
		}
		else if (PartsCollisionCheck(number, 3) == true) {
			score += 8.0f;
		}
		else if (PartsCollisionCheck(number, 4) == true) {
			score += 4.0f;
		}
		scoreFlag[number] = true;
	}
}

// パーツ紛失
void StageOne::PartsLost(unsigned int number)
{
	// パーツが画面外に出たら、初期位置に戻す
	if (PartsPosition[number].x < -64 || 1216 < PartsPosition[number].x ||
		PartsPosition[number].y < -64 || 656 < PartsPosition[number].y) {
		PartsPosition[number] = DefaultPartsPosition[number];
		catchFlag[number] = false;
	}
}

// リセット
void StageOne::Reset()
{
	score = 0;
	alpha = 0;
	for (int i = 0; i < partsNumber; i++) {
		catchFlag[i] = false;
		drawFlag[i] = false;
		scoreFlag[i] = false;
		PartsPosition[i] = DefaultPartsPosition[i];
	}
}

// パーツの当たり判定をチェック
bool StageOne::PartsCollisionCheck(unsigned int number, unsigned int number2)
{
	if (PerfectPartsPosition[number].x - judge[number2] < PartsPosition[number].x &&
		PartsPosition[number].x < PerfectPartsPosition[number].x + judge[number2] &&
		PerfectPartsPosition[number].y - judge[number2] < PartsPosition[number].y &&
		PartsPosition[number].y < PerfectPartsPosition[number].y + judge[number2]) {
		return true;
	}
	else {
		return false;
	}
}

// パーツ持っているかをチェック
bool StageOne::CatchCheck()
{
	if (catchFlag[0] == false && catchFlag[1] == false && catchFlag[2] == false &&
		catchFlag[3] == false && catchFlag[4] == false) {
		return true;
	}
	else {
		return false;
	}
}

// パーツが全て並べられたかをチェック
bool StageOne::DrawCheck()
{
	if (drawFlag[0] == true && drawFlag[1] == true && drawFlag[2] == true &&
		drawFlag[3] == true && drawFlag[4] == true) {
		return true;
	}
	else {
		return false;
	}
}