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
}

// 描画
void StageOne::Draw()
{
	// 顔
	DrawGraph(384, 104, face, TRUE);

	// 目
	DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
	DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);

	// 手
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
	}
}

// 当たり判定
void StageOne::Collision()
{
	// マウスをクリックしていないとき、掴みフラグをオフにする
	for (int i = 0; i < 2; i++) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[i] = 0;
		}
	}

	// 左目のパーツの当たり判定
	if (PartsPosition[0].x < MousePosition.x && MousePosition.x < PartsPosition[0].x + 128 &&
		PartsPosition[0].y < MousePosition.y && MousePosition.y < PartsPosition[0].y + 128) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
			catchFlag[0] = 1;
		}
	}
	// 右目のパーツの当たり判定
	else if (PartsPosition[1].x < MousePosition.x && MousePosition.x < PartsPosition[1].x + 128 &&
		PartsPosition[1].y < MousePosition.y && MousePosition.y < PartsPosition[1].y + 128) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
			catchFlag[1] = 1;
		}
	}

	// 左目の掴みフラグがオンになったら、マウスに追尾する
	if (catchFlag[0] == 1) {
		PartsPosition[0].x = MousePosition.x - 64;
		PartsPosition[0].y = MousePosition.y - 64;
	}
	// 右目の掴みフラグがオンになったら、マウスに追尾する
	else if (catchFlag[1] == 1) {
		PartsPosition[1].x = MousePosition.x - 64;
		PartsPosition[1].y = MousePosition.y - 64;
	}
}

// リセット
void StageOne::Reset()
{
	for (int i = 0; i < 2; i++) {
		catchFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}