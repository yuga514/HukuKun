#include "StageOne.h"

// コンストラクタ
StageOne::StageOne()
{
}

// デストラクタ
StageOne::~StageOne()
{
	DeleteGraph(face);
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	DeleteGraph(eye1);
	DeleteGraph(eye2);
}

// 初期化
void StageOne::Initialize()
{
	// 画像などのリソースデータの読み込み
	face = LoadGraph("Resources/sampleface2.png");
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	eye1 = LoadGraph("Resources/eye1.png");
	eye2 = LoadGraph("Resources/eye2.png");
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

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		if (alpha < 255) {
			alpha += 3;
		}
	}

	if (380 < PartsPosition[0].x && PartsPosition[0].x < 580 &&
		100 < PartsPosition[0].y && PartsPosition[0].y < 300 && scoreFlag[0] == 0 && drawFlag[0] == 1) {
		score += 50;
		scoreFlag[0] = 1;
	}
	if (572 < PartsPosition[1].x && PartsPosition[1].x < 772 &&
		100 < PartsPosition[1].y && PartsPosition[1].y < 200 && scoreFlag[1] == 0 && drawFlag[1] == 1) {
		score += 50;
		scoreFlag[1] = 1;
	}

	// 次のシーンへのフラグをオンにする
	if (alpha == 255) {
		nextSceneFlag = 1;
	}	
}

// 描画
void StageOne::Draw()
{
	// 顔
	DrawGraph(FacePosition.x, FacePosition.y, face, TRUE);

	// 目
	if (drawFlag[0] == 0) {
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
	}
	if (drawFlag[1] == 0) {
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);
	}

	// 結果発表
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);
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

// 当たり判定のテンプレート
void StageOne::CollisionTemplate(unsigned int number)
{
	// 左目の当たり判定
	if (drawFlag[number] == 0) {
		// マウスをクリックしていないとき、パーツを離す
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = 0;
		}
		// 左目のパーツの当たり判定
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
				catchFlag[number] = 1;
			}
		}
		// 左目を掴んでいるとき、マウスに追尾する
		if (catchFlag[number] == 1) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// 左目のパーツと顔の当たり判定
		if (FacePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < FacePosition.x + 512 &&
			FacePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < FacePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = 1;
			}
		}
	}
}

// リセット
void StageOne::Reset()
{
	for (int i = 0; i < number; i++) {
		catchFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}