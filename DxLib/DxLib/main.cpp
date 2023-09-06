#include "DxLib.h"
#include <DirectXMath.h>

const char TITLE[] = "HukuKun";

const int WIN_WIDTH = 1280; // �E�B���h�E����
const int WIN_HEIGHT = 720; // �E�B���h�E�c��

//---------  �Q�[�����[�v�Ŏg���֐���������  ---------//

// �V�[������
void SceneChange();

//---------  �Q�[�����[�v�Ŏg���֐������܂�  ---------//

//---------  �Q�[�����[�v�Ŏg���ϐ���������  ---------//

using XMINT2 = DirectX::XMINT2; // DirectX::���ȗ�

char keys[256] = { 0 }; // �ŐV�̃L�[�{�[�h���p
char oldkeys[256] = { 0 }; // 1���[�v�i�t���[���j�O�̃L�[�{�[�h���

int button = 0;
unsigned int scene = 0;

XMINT2 ClickPosition = {};
XMINT2 MousePosition = {};

//---------  �Q�[�����[�v�Ŏg���ϐ������܂�  ---------//

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txt���쐬���Ȃ�
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE); // �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); // ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0); // ��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0x00); // ��ʂ̔w�i�F��ݒ肷��

	// Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int title = LoadGraph("Resources/test1.png");
	int background = LoadGraph("Resources/test2.png");
	int hand1 = LoadGraph("Resources/hand1.png");
	int hand2 = LoadGraph("Resources/hand2.png");
	int face1 = LoadGraph("Resources/sampleface.png");
	int face2 = LoadGraph("Resources/sampleface2.png");

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

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&MousePosition.x, &MousePosition.y);

		if (scene == 0) {
			// ����
		}
		if (scene == 1) {
			// ����
		}
		if (scene == 2) {
			// �}�E�X��\��
			SetMouseDispFlag(FALSE);
		}

		// �V�[������
		SceneChange();

		// �`�揈��

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
			// ���Ă�
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
			}
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
			}
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
	// Dx���C�u�����I������
	DxLib_End();

	return 0;
}

// �V�[������
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
		// ����
	}
}