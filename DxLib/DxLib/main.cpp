#include "DxLib.h"

const char TITLE[] = "���΂�";

const int WIN_WIDTH = 1280; // �E�B���h�E����
const int WIN_HEIGHT = 720; // �E�B���h�E�c��

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

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; // �ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 }; // 1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	unsigned int scene = 0;
	int MouseX, MouseY;

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�


		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&MouseX, &MouseY);

		if (scene == 0) {
			// ���N���b�N
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				scene = 1;
			}
		}
		if (scene == 1) {
			// �}�E�X��\��
			SetMouseDispFlag(FALSE);


		}


		// �`�揈��

		if (scene == 0) {
			DrawGraph(0, 0, title, TRUE);
		}
		if (scene == 1) {
			DrawGraph(0, 0, background, TRUE);
			// ���N���b�N
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				DrawGraph(MouseX - 32, MouseY - 32, hand1, TRUE);
			}
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				DrawGraph(MouseX - 32, MouseY - 32, hand2, TRUE);
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