#include "DxLib.h"

const char TITLE[] = "福笑い";

const int WIN_WIDTH = 1280; // ウィンドウ横幅
const int WIN_HEIGHT = 720; // ウィンドウ縦幅

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

	// ゲームループで使う変数の宣言
	char keys[256] = { 0 }; // 最新のキーボード情報用
	char oldkeys[256] = { 0 }; // 1ループ（フレーム）前のキーボード情報

	unsigned int scene = 0;
	int MouseX, MouseY;

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは１フレーム前のキーボード情報として保存


		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		// マウスの位置を取得
		GetMousePoint(&MouseX, &MouseY);

		if (scene == 0) {
			// 左クリック
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				scene = 1;
			}
		}
		if (scene == 1) {
			// マウス非表示
			SetMouseDispFlag(FALSE);


		}


		// 描画処理

		if (scene == 0) {
			DrawGraph(0, 0, title, TRUE);
		}
		if (scene == 1) {
			DrawGraph(0, 0, background, TRUE);
			// 左クリック
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				DrawGraph(MouseX - 32, MouseY - 32, hand1, TRUE);
			}
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				DrawGraph(MouseX - 32, MouseY - 32, hand2, TRUE);
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