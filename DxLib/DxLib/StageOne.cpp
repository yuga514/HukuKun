#include "StageOne.h"

// �R���X�g���N�^
StageOne::StageOne()
{
}

// �f�X�g���N�^
StageOne::~StageOne()
{
	DeleteGraph(face);
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	DeleteGraph(eye1);
	DeleteGraph(eye2);
}

// ������
void StageOne::Initialize()
{
	// �摜�Ȃǂ̃��\�[�X�f�[�^�̓ǂݍ���
	face = LoadGraph("Resources/sampleface2.png");
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	eye1 = LoadGraph("Resources/eye1.png");
	eye2 = LoadGraph("Resources/eye2.png");
}

// �X�V
void StageOne::Update()
{
	// �}�E�X��\��
	SetMouseDispFlag(FALSE);

	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	// �����蔻��
	Collision();
}

// �`��
void StageOne::Draw()
{
	// ��
	DrawGraph(384, 104, face, TRUE);

	// ��
	DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
	DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);

	// ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
	}
}

// �����蔻��
void StageOne::Collision()
{
	// �}�E�X���N���b�N���Ă��Ȃ��Ƃ��A�͂݃t���O���I�t�ɂ���
	for (int i = 0; i < 2; i++) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[i] = 0;
		}
	}

	// ���ڂ̃p�[�c�̓����蔻��
	if (PartsPosition[0].x < MousePosition.x && MousePosition.x < PartsPosition[0].x + 128 &&
		PartsPosition[0].y < MousePosition.y && MousePosition.y < PartsPosition[0].y + 128) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
			catchFlag[0] = 1;
		}
	}
	// �E�ڂ̃p�[�c�̓����蔻��
	else if (PartsPosition[1].x < MousePosition.x && MousePosition.x < PartsPosition[1].x + 128 &&
		PartsPosition[1].y < MousePosition.y && MousePosition.y < PartsPosition[1].y + 128) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
			catchFlag[1] = 1;
		}
	}

	// ���ڂ̒͂݃t���O���I���ɂȂ�����A�}�E�X�ɒǔ�����
	if (catchFlag[0] == 1) {
		PartsPosition[0].x = MousePosition.x - 64;
		PartsPosition[0].y = MousePosition.y - 64;
	}
	// �E�ڂ̒͂݃t���O���I���ɂȂ�����A�}�E�X�ɒǔ�����
	else if (catchFlag[1] == 1) {
		PartsPosition[1].x = MousePosition.x - 64;
		PartsPosition[1].y = MousePosition.y - 64;
	}
}

// ���Z�b�g
void StageOne::Reset()
{
	for (int i = 0; i < 2; i++) {
		catchFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}