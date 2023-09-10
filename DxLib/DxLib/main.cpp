#include "StageOne.h"

const char TITLENAME[] = "福来たる";

const int WIN_WIDTH = 1280; // ウィンドウ横幅
const int WIN_HEIGHT = 720; // ウィンドウ縦幅

//---------  ゲームループで使う関数ここから  ---------//

// シーン推移
void SceneChange();

// リセット
void Reset();

// ボタンの当たり判定
bool ButtonCollision(unsigned int number);

//---------  ゲームループで使う関数ここまで  ---------//

//---------  ゲームループで使う変数ここから  ---------//

char keys[256] = { 0 }; // 最新のキーボード情報用
char oldkeys[256] = { 0 }; // 1ループ（フレーム）前のキーボード情報

int buttonLog = 0;
unsigned int scene = 0;

const XMINT2 ButtonPosition[5] = { { 512,360 }, { -15000,-15000 }, { 100,606 }, { 512,606 }, { 924,606 } };
XMINT2 ClickPosition = {};
XMINT2 MousePosition = {};

StageOne* stageOne = nullptr;

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

//---------  ゲームループで使う変数ここまで  ---------//

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを作成しない
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	// ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLENAME); // タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); // 画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0); // 画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0x00); // 画面の背景色を設定する

	// Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int button[5] = {};
	button[0] = LoadGraph("Resources/button/button4.png");
	button[1] = LoadGraph("Resources/button/button5.png");
	button[2] = LoadGraph("Resources/button/button.png");
	button[3] = LoadGraph("Resources/button/button2.png");
	button[4] = LoadGraph("Resources/button/button3.png");
	int hand = LoadGraph("Resources/hand3.png");
	int title = LoadGraph("Resources/title.png");
	int background = LoadGraph("Resources/test2.png");
	int ghost = LoadGraph("Resources/ghost/ghost.png");
	int okame = LoadGraph("Resources/okame/okame.png");

	// ステージ1生成
	stageOne = new StageOne();
	stageOne->Initialize();

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ---------//

		// 更新処理

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

		// 描画処理
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (scene == TITLE) {
			DrawGraph(0, 0, title, TRUE);
			DrawGraph(ButtonPosition[0].x, ButtonPosition[0].y, button[0], TRUE);
			DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
		}
		if (scene == SAMPLE1) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[2], TRUE);
			DrawGraph(384, 104, ghost, TRUE);
			DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
		}
		if (scene == STAGE1) {
			DrawGraph(0, 0, background, TRUE);
			stageOne->Draw();
		}
		if (scene == SAMPLE2) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(384, 104, okame, TRUE);
		}

		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip(); //（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// デストラクタ
	DeleteGraph(title);
	DeleteGraph(background);
	DeleteGraph(ghost);
	stageOne->~StageOne();

	// Dxライブラリ終了処理
	DxLib_End();

	return 0;
}

// シーン推移
void SceneChange()
{
	if (scene == 0) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(0) == true) {
			scene = 1;
		}
	}
	if (scene == 1) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(2) == true) {
			scene = 2;
		}
	}
	if (scene == 2) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && stageOne->GetAlpha() == 255) {
			if (50 <= stageOne->GetScore()) {
				scene = 3;
			}
			if (stageOne->GetScore() < 50) {
				scene = 0;
				Reset();
			}
		}
	}
}

// リセット
void Reset()
{
	stageOne->Reset();
}

// ボタンの当たり判定
bool ButtonCollision(unsigned int number)
{
	if (ButtonPosition[number].x < MousePosition.x && MousePosition.x < ButtonPosition[number].x + 256 &&
		ButtonPosition[number].y < MousePosition.y && MousePosition.y < ButtonPosition[number].y + 64) {
		return true;
	}
}