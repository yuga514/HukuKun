#include "StageOne.h"

const char TITLENAME[] = "��������";

const int WIN_WIDTH = 1280; // �E�B���h�E����
const int WIN_HEIGHT = 720; // �E�B���h�E�c��

//---------  �Q�[�����[�v�Ŏg���֐���������  ---------//

// ���[�h
void Load();

// �f���[�g
void Delete();

// �V�[������
void SceneChange();

// ���Z�b�g
void Reset();

// �{�^���̓����蔻��
bool ButtonCollision(unsigned int number);

//---------  �Q�[�����[�v�Ŏg���֐������܂�  ---------//

//---------  �Q�[�����[�v�Ŏg���ϐ���������  ---------//

char keys[256] = { 0 }; // �ŐV�̃L�[�{�[�h���p
char oldkeys[256] = { 0 }; // 1���[�v�i�t���[���j�O�̃L�[�{�[�h���

int buttonLog = 0;
unsigned int scene = 0;

const XMINT2 ButtonPosition[4] = { { 512,360 }, { 512,606 }, { 100,606 }, { 924,606 } };
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

// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
int button[5] = {};
int hand = 0;
int title = 0;
int background = 0;
int ghost = 0;
int okame = 0;

//---------  �Q�[�����[�v�Ŏg���ϐ������܂�  ---------//

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txt���쐬���Ȃ�
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLENAME); // �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); // ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0); // ��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0x00); // ��ʂ̔w�i�F��ݒ肷��

	// Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̓ǂݍ���
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

	// �X�e�[�W1����
	stageOne = new StageOne();
	stageOne->Initialize();

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ---------//

		// �X�V����

		// �}�E�X��\��
		SetMouseDispFlag(FALSE);

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&MousePosition.x, &MousePosition.y);

		if (scene == TITLE) {
			// ����
		}
		if (scene == SAMPLE1) {
			// ����
		}
		if (scene == STAGE1) {
			stageOne->Update();
		}
		if (scene == SAMPLE2) {
			// ����
		}

		// �V�[������
		SceneChange();

		// �`�揈��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (scene == TITLE) {
			DrawGraph(0, 0, title, TRUE);
			DrawGraph(ButtonPosition[0].x, ButtonPosition[0].y, button[0], TRUE);
			DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
		}
		if (scene == SAMPLE1) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(384, 104, ghost, TRUE);
			DrawGraph(ButtonPosition[1].x, ButtonPosition[1].y, button[1], TRUE);
			DrawGraph(MousePosition.x - 23, MousePosition.y - 13, hand, TRUE);
			// �X�R�A50�ȏ�ŃN���A
			DrawFormatString(0, 0, GetColor(0, 0, 0), "�X�R�A50�ȏ�ŃN���A");
		}
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
		if (scene == SAMPLE2) {
			DrawGraph(0, 0, background, TRUE);
			DrawGraph(384, 104, okame, TRUE);
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip(); //�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// �f�X�g���N�^
	Delete();
	stageOne->~StageOne();

	// Dx���C�u�����I������
	DxLib_End();

	return 0;
}

// �f���[�g
void Delete()
{
	for (int i = 0; i < 5; i++) {
		DeleteGraph(button[i]);
	}
	DeleteGraph(hand);
	DeleteGraph(title);
	DeleteGraph(background);
	DeleteGraph(ghost);
	DeleteGraph(okame);
}

// �V�[������
void SceneChange()
{
	if (scene == TITLE) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(0) == true) {
			scene = SAMPLE1;
		}
	}
	if (scene == SAMPLE1) {
		if (GetMouseInputLog(&buttonLog, &ClickPosition.x, &ClickPosition.y, TRUE) == 0 &&
			(buttonLog & MOUSE_INPUT_LEFT) != 0 && ButtonCollision(1) == true) {
			scene = STAGE1;
		}
	}
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

// ���Z�b�g
void Reset()
{
	stageOne->Reset();
}

// �{�^���̓����蔻��
bool ButtonCollision(unsigned int number)
{
	if (ButtonPosition[number].x < MousePosition.x && MousePosition.x < ButtonPosition[number].x + 256 &&
		ButtonPosition[number].y < MousePosition.y && MousePosition.y < ButtonPosition[number].y + 64) {
		return true;
	}
	else {
		return false;
	}
}