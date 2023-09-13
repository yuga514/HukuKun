#include "GameScene.h"

// コンストラクタ
GameScene::GameScene()
{
}

// デストラクタ
GameScene::~GameScene()
{
	// フォント
	RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);
	DeleteFontToHandle(fontHandle);

	// 画像
	for (int i = 0; i < 16; i++) {
		DeleteGraph(button[i]);
	}
	for (int i = 0; i < 4; i++) {
		DeleteGraph(rule[i]);
	}
	DeleteGraph(hand);
	DeleteGraph(title);
	DeleteGraph(background);
	DeleteGraph(clear);
	DeleteGraph(ghost);
	for (int i = 0; i < 2; i++) {
		DeleteGraph(okame[i]);
		DeleteGraph(hyottoko[i]);
		DeleteGraph(franken[i]);
	}

	// BGM・SE
	DeleteSoundMem(titleBGM);
	DeleteSoundMem(kuonBGM);
	DeleteSoundMem(buttonSE);
	DeleteSoundMem(hajimeSE);
	DeleteSoundMem(successSE);
	DeleteSoundMem(failedSE);
	DeleteSoundMem(clearSE);

	// クラス
	stageOne->~StageOne();
	stageTwo->~StageTwo();
	stageThree->~StageThree();
	stageFour->~StageFour();
}

// 初期化
void GameScene::Initialize()
{
	// リソースデータの読み込み

	// フォント
	font_path = "Resources/font/DFP勘亭流.ttf";
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	fontHandle = CreateFontToHandle("ＤＦＰ勘亭流", 64, 8);

	// 画像
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
	button[14] = LoadGraph("Resources/button/button8Black.png");
	button[15] = LoadGraph("Resources/button/button8.png");
	rule[0] = LoadGraph("Resources/rule/rule1.png");
	rule[1] = LoadGraph("Resources/rule/rule2.png");
	rule[2] = LoadGraph("Resources/rule/rule3.png");
	rule[3] = LoadGraph("Resources/rule/rule4.png");
	hand = LoadGraph("Resources/hand/hand3.png");
	title = LoadGraph("Resources/background/title.png");
	background = LoadGraph("Resources/background/background.png");
	clear = LoadGraph("Resources/background/clear.png");
	ghost = LoadGraph("Resources/ghost/ghost.png");
	okame[0] = LoadGraph("Resources/okame/okameBlack.png");
	okame[1] = LoadGraph("Resources/okame/okame.png");
	hyottoko[0] = LoadGraph("Resources/hyottoko/hyottokoBlack.png");
	hyottoko[1] = LoadGraph("Resources/hyottoko/hyottoko.png");
	franken[0] = LoadGraph("Resources/franken/frankenBlack.png");
	franken[1] = LoadGraph("Resources/franken/franken.png");

	// BGM・SE
	titleBGM = LoadSoundMem("Resources/audio/title.mp3");
	kuonBGM = LoadSoundMem("Resources/audio/kuon.mp3");
	buttonSE = LoadSoundMem("Resources/audio/button.mp3");
	hajimeSE = LoadSoundMem("Resources/audio/hajime.mp3");
	successSE = LoadSoundMem("Resources/audio/success.mp3");
	failedSE = LoadSoundMem("Resources/audio/failed.mp3");
	clearSE = LoadSoundMem("Resources/audio/clear.mp3");

	// 音調調整
	ChangeVolumeSoundMem(255 * 50 / 100, titleBGM);
	ChangeVolumeSoundMem(255 * 50 / 100, kuonBGM);
	ChangeVolumeSoundMem(255 * 500 / 100, buttonSE);
	ChangeVolumeSoundMem(255 * 100 / 100, hajimeSE);
	ChangeVolumeSoundMem(255 * 100 / 100, successSE);
	ChangeVolumeSoundMem(255 * 100 / 100, failedSE);
	ChangeVolumeSoundMem(255 * 100 / 100, clearSE);

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
			if (ButtonCollision(1) == true) {
				scene = RULE1;
			}
			if (ButtonCollision(2) == true) {
				scene = SELECT1;
			}
		}
	}
	// ルール1
	if (scene == RULE1) {
		RuleCollision(TITLE, RULE2);
	}
	// ルール2
	if (scene == RULE2) {
		RuleCollision(RULE1, RULE3);
	}
	// ルール3
	if (scene == RULE3) {
		RuleCollision(RULE2, RULE4);
	}
	// ルール4
	if (scene == RULE4) {
		RuleCollision(RULE3, TITLE);
	}
	// 顔選択1
	if (scene == SELECT1) {
		SelectCollision(SAMPLE1, TITLE, SELECT2, true);
	}
	// 顔選択2
	if (scene == SELECT2) {
		SelectCollision(SAMPLE2, SELECT1, SELECT3, stageTwo->GetSelectFlag());
	}
	// 顔選択3
	if (scene == SELECT3) {
		SelectCollision(SAMPLE3, SELECT2, SELECT4, stageThree->GetSelectFlag());
	}
	// 顔選択4
	if (scene == SELECT4) {
		SelectCollision(SAMPLE4, SELECT3, TITLE, stageFour->GetSelectFlag());
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
			if (ButtonCollision(2) == true && 50 <= stageOne->GetScore()) {
				scene = SAMPLE2;
			}
			if (ButtonCollision(3) == true) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4) == true) {
				scene = SAMPLE1;
				stageOne->Reset();
			}
		}
		stageOne->Update();
	}
	// サンプル2
	if (scene == SAMPLE2) {
		stageTwo->SetSelectFlag();
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE2;
		}
	}
	// ステージ2
	if (scene == STAGE2) {
		if (ButtonCheck() == true && stageTwo->GetAlpha() == 255) {
			if (ButtonCollision(2) == true && 60 <= stageTwo->GetScore()) {
				scene = SAMPLE3;
			}
			if (ButtonCollision(3) == true) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4) == true) {
				scene = SAMPLE2;
				stageTwo->Reset();
			}
		}
		stageTwo->Update();
	}
	// サンプル3
	if (scene == SAMPLE3) {
		stageThree->SetSelectFlag();
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE3;
		}
	}
	// ステージ3
	if (scene == STAGE3) {
		if (ButtonCheck() == true && stageThree->GetAlpha() == 255) {
			if (ButtonCollision(2) == true && 70 <= stageThree->GetScore()) {
				scene = SAMPLE4;
			}
			if (ButtonCollision(3) == true) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4) == true) {
				scene = SAMPLE3;
				stageThree->Reset();
			}
		}
		stageThree->Update();
	}
	// サンプル4
	if (scene == SAMPLE4) {
		stageFour->SetSelectFlag();
		if (ButtonCheck() == true && ButtonCollision(2) == true) {
			scene = STAGE4;
		}
	}
	// ステージ4
	if (scene == STAGE4) {
		if (ButtonCheck() == true && stageFour->GetAlpha() == 255) {
			if (ButtonCollision(2) == true && 80 <= stageFour->GetScore()) {
				scene = CLEAR;
			}
			if (ButtonCollision(3) == true) {
				scene = TITLE;
				Reset();
			}
			if (ButtonCollision(4) == true) {
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
		DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[2], TRUE);
		if (ButtonCollision(1) == true) {
			DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[3], TRUE);
		}
		DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[4], TRUE);
		if (ButtonCollision(2) == true) {
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[5], TRUE);
		}
		DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
	}
	// ルール1
	if (scene == RULE1) {
		RuleDraw(rule[0]);
	}
	// ルール2
	if (scene == RULE2) {
		RuleDraw(rule[1]);
	}
	// ルール3
	if (scene == RULE3) {
		RuleDraw(rule[2]);
	}
	// ルール4
	if (scene == RULE4) {
		RuleDraw(rule[3]);
	}
	// 顔選択1
	if (scene == SELECT1) {
		SelectDraw(ghost, ghost, true);
	}
	// 顔選択2
	if (scene == SELECT2) {
		SelectDraw(okame[0], okame[1], stageTwo->GetSelectFlag());
	}
	// 顔選択3
	if (scene == SELECT3) {
		SelectDraw(hyottoko[0], hyottoko[1], stageThree->GetSelectFlag());
	}
	// 顔選択4
	if (scene == SELECT4) {
		SelectDraw(franken[0], franken[1], stageFour->GetSelectFlag());
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
		SampleDraw(okame[1], 60);
	}
	// ステージ2
	if (scene == STAGE2) {
		DrawGraph(0, 0, background, TRUE);
		stageTwo->Draw();
		StageDraw(okame[1], 60, stageTwo->GetScore(), stageTwo->GetAlpha());
	}
	// サンプル3
	if (scene == SAMPLE3) {
		SampleDraw(hyottoko[1], 70);
	}
	// ステージ3
	if (scene == STAGE3) {
		DrawGraph(0, 0, background, TRUE);
		stageThree->Draw();
		StageDraw(hyottoko[1], 70, stageThree->GetScore(), stageThree->GetAlpha());
	}
	// サンプル4
	if (scene == SAMPLE4) {
		SampleDraw(franken[1], 80);
	}
	// ステージ4
	if (scene == STAGE4) {
		DrawGraph(0, 0, background, TRUE);
		stageFour->Draw();
		StageDraw(franken[1], 80, stageFour->GetScore(), stageFour->GetAlpha());
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

// サウンド
void GameScene::Sound()
{
	// タイトル
	if (scene == TITLE) {
		// BGM停止
		if (CheckSoundMem(kuonBGM) == 1) {
			StopSoundMem(kuonBGM);
		}
		// BGM再生
		if (CheckSoundMem(titleBGM) == 0) {
			PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP);
		}
		// SE再生
		if (ButtonCollision(0) == true || ButtonCollision(1) == true || ButtonCollision(2) == true) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
				PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
			}
		}
	}
	// ルール1
	if (scene == RULE1) {
		RuleSound();
	}
	// ルール2
	if (scene == RULE2) {
		RuleSound();
	}
	// ルール3
	if (scene == RULE3) {
		RuleSound();
	}
	// ルール4
	if (scene == RULE4) {
		RuleSound();
	}
	// 顔選択1
	if (scene == SELECT1) {
		SelectSound(true);
	}
	// 顔選択2
	if (scene == SELECT2) {
		SelectSound(stageTwo->GetSelectFlag());
	}
	// 顔選択3
	if (scene == SELECT3) {
		SelectSound(stageThree->GetSelectFlag());
	}
	// 顔選択4
	if (scene == SELECT4) {
		SelectSound(stageFour->GetSelectFlag());
	}
	// サンプル1
	if (scene == SAMPLE1) {
		SampleSound();
	}
	// ステージ1
	if (scene == STAGE1) {
		StageSound(50, stageOne->GetScore(), stageOne->GetAlpha());
	}
	// サンプル2
	if (scene == SAMPLE2) {
		SampleSound();
	}
	// ステージ2
	if (scene == STAGE2) {
		StageSound(60, stageTwo->GetScore(), stageTwo->GetAlpha());
	}
	// サンプル3
	if (scene == SAMPLE3) {
		SampleSound();
	}
	// ステージ3
	if (scene == STAGE3) {
		StageSound(70, stageThree->GetScore(), stageThree->GetAlpha());
	}
	// サンプル4
	if (scene == SAMPLE4) {
		SampleSound();
	}
	// ステージ4
	if (scene == STAGE4) {
		StageSound(80, stageFour->GetScore(), stageFour->GetAlpha());
	}
	// クリア
	if (scene == CLEAR) {
		if(clearSEflag == true) {
			PlaySoundMem(clearSE, DX_PLAYTYPE_BACK);
			clearSEflag = false;
		}
		if (ButtonCollision(2) == true) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
				PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
			}
		}
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		SEflag = true;
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		SEflag = false;
	}
}

// 遊び方説明の時の当たり判定
void GameScene::RuleCollision(unsigned int scene1, unsigned int scene2)
{
	if (ButtonCheck() == true) {
		if (ButtonCollision(3) == true) {
			scene = scene1;
		}
		if (ButtonCollision(4) == true) {
			scene = scene2;
		}
	}
}

// 顔選択の時の当たり判定
void GameScene::SelectCollision(unsigned int scene1, unsigned int scene2, unsigned int scene3, bool selectFlag)
{
	if (ButtonCheck() == true) {
		if (ButtonCollision(2) == true && selectFlag == true) {
			scene = scene1;
		}
		if (ButtonCollision(3) == true) {
			scene = scene2;
		}
		if (ButtonCollision(4) == true) {
			scene = scene3;
		}
	}
}

// 遊び方説明の時に描画するもの
void GameScene::RuleDraw(int graphHandle)
{
	DrawGraph(0, 0, graphHandle, TRUE);
	DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[14], TRUE);
	if (ButtonCollision(3) == true) {
		DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[15], TRUE);
	}
	if (scene == RULE1) {
		DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[8], TRUE);
		if (ButtonCollision(3) == true) {
			DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[9], TRUE);
		}
	}
	DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[10], TRUE);
	if (ButtonCollision(4) == true) {
		DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[11], TRUE);
	}
	if (scene == RULE4) {
		DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[8], TRUE);
		if (ButtonCollision(4) == true) {
			DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[9], TRUE);
		}
	}
	DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
}

// 顔選択の時に描画するもの
void GameScene::SelectDraw(int graphHandle1, int graphHandle2, bool selectFlag)
{
	DrawGraph(0, 0, background, TRUE);
	DrawGraph(384, 104, graphHandle1, TRUE);
	if (selectFlag == true) {
		DrawGraph(384, 104, graphHandle2, TRUE);
		DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[0], TRUE);
		if (ButtonCollision(2) == true) {
			DrawGraph(ButtonPosition[2].x, ButtonPosition[2].y, button[1], TRUE);
		}
	}
	DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[14], TRUE);
	if (ButtonCollision(3) == true) {
		DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[15], TRUE);
	}
	if (scene == SELECT1) {
		DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[8], TRUE);
		if (ButtonCollision(3) == true) {
			DrawGraph(ButtonPosition[3].x, ButtonPosition[3].y, button[9], TRUE);
		}
	}
	DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[10], TRUE);
	if (ButtonCollision(4) == true) {
		DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[11], TRUE);
	}
	if (scene == SELECT4) {
		DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[8], TRUE);
		if (ButtonCollision(4) == true) {
			DrawGraph(ButtonPosition[4].x, ButtonPosition[4].y, button[9], TRUE);
		}
	}
	DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
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
		if (norma <= (unsigned int)score) {
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

// 遊び方説明の時に再生するもの
void GameScene::RuleSound()
{
	if (ButtonCollision(3) == true || ButtonCollision(4) == true) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
			PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
		}
	}
}

// 顔選択の時に再生するもの
void GameScene::SelectSound(bool selectFlag)
{
	if (ButtonCollision(2) == true && selectFlag == true || ButtonCollision(3) == true || ButtonCollision(4) == true) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
			PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
		}
	}
}

// サンプル表示の時に再生するもの
void GameScene::SampleSound()
{
	// BGM停止
	if (CheckSoundMem(titleBGM) == 1) {
		StopSoundMem(titleBGM);
	}
	// BGM再生
	if (CheckSoundMem(kuonBGM) == 0) {
		PlaySoundMem(kuonBGM, DX_PLAYTYPE_LOOP);
	}
	// SE再生
	if (ButtonCollision(2) == true) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
			PlaySoundMem(hajimeSE, DX_PLAYTYPE_BACK);
		}
	}
}

// ステージ終了の時に再生するもの
void GameScene::StageSound(unsigned int norma, float score, unsigned int alpha)
{
	if (alpha == 252) {
		if (norma <= (unsigned int)score) {
			PlaySoundMem(successSE, DX_PLAYTYPE_BACK);
		}
		if ((unsigned int)score < norma) {
			PlaySoundMem(failedSE, DX_PLAYTYPE_BACK);
		}
	}

	if (alpha == 255) {
		if (ButtonCollision(2) == true && norma <= (unsigned int)score || ButtonCollision(3) == true || ButtonCollision(4) == true) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && SEflag == true) {
				PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
			}
		}
	}
}

// リセット
void GameScene::Reset()
{
	clearSEflag = true;
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