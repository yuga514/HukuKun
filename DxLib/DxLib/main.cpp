#include "DxLib.h"
#include <DirectXMath.h>

const char TITLE[] = "HukuKun";

const int WIN_WIDTH = 1280; // ウィンドウ横幅
const int WIN_HEIGHT = 720; // ウィンドウ縦幅

//---------  ゲームループで使う関数ここから  ---------//

// シーン推移
void SceneChange();

//---------  ゲームループで使う関数ここまで  ---------//

//---------  ゲームループで使う変数ここから  ---------//

using XMINT2 = DirectX::XMINT2; // DirectX::を省略

char keys[256] = { 0 }; // 最新のキーボード情報用
char oldkeys[256] = { 0 }; // 1ループ（フレーム）前のキーボード情報

int button = 0;
unsigned int scene = 0;

XMINT2 ClickPosition = {};
XMINT2 MousePosition = {};

//---------  ゲームループで使う変数ここまで  ---------//

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを作成しない
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	// ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE); // タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); // 画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0); // 画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0x00); // 画面の背景色を設定する

	// Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int title = LoadGraph("Resources/test1.png");
	int background = LoadGraph("Resources/test2.png");
	int hand1 = LoadGraph("Resources/hand1.png");
	int hand2 = LoadGraph("Resources/hand2.png");
	int face1 = LoadGraph("Resources/sampleface.png");
	int face2 = LoadGraph("Resources/sampleface2.png");

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

		// マウスの位置を取得
		GetMousePoint(&MousePosition.x, &MousePosition.y);

		if (scene == 0) {
			// 処理
		}
		if (scene == 1) {
			// 処理
		}
		if (scene == 2) {
			// マウス非表示
			SetMouseDispFlag(FALSE);
		}

		// シーン推移
		SceneChange();

		// 描画処理

		if (scene == 0) {
			DrawGraph(0, 0, title, TRUE);
		}
		if (scene == 1) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(384, 104, face1, TRUE);
		}
		if (scene == 2) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(384, 104, face2, TRUE);
			// おてて
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
			}
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
			}
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
	// Dxライブラリ終了処理
	DxLib_End();

	return 0;
}

// シーン推移
void SceneChange() {
	if (scene == 0) {		
		if (GetMouseInputLog(&button, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 && (button & MOUSE_INPUT_LEFT) != 0) {
			scene = 1;
		}
	}
	if (scene == 1) {
		if (GetMouseInputLog(&button, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 && (button & MOUSE_INPUT_LEFT) != 0) {
			scene = 2;
		}
	}
	if (scene == 2) {
		// 処理
	}
}