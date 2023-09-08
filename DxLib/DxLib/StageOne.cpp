#include "StageOne.h"

// �R���X�g���N�^
StageOne::StageOne()
{
}

// �f�X�g���N�^
StageOne::~StageOne()
{
	DeleteGraph(plate);
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	for (int i = 0; i < partsNumber; i++) {
		DeleteGraph(parts[i]);
	}
}

// ������
void StageOne::Initialize()
{
	// �摜�Ȃǂ̃��\�[�X�f�[�^�̓ǂݍ���
	plate = LoadGraph("Resources/ghost/plate.png");
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	parts[0] = LoadGraph("Resources/ghost/LeftEye.png");
	parts[1] = LoadGraph("Resources/ghost/RightEye.png");
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

	// �X�R�A���Z
	ScoreAddition();

	// ���ʔ��\
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		if (alpha < 255) {
			alpha += 3;
		}
	}
}

// �`��
void StageOne::Draw()
{
	// ��
	DrawGraph(PlatePosition.x, PlatePosition.y, plate, TRUE);

	// ��
	if (drawFlag[0] == 0) {
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, parts[0], TRUE);
	}
	if (drawFlag[1] == 0) {
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, parts[1], TRUE);
	}

	// ���ʔ��\
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, parts[0], TRUE);
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, parts[1], TRUE);
	}

	// ��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
	}

	// �X�R�A
	DrawFormatString(0, 0, GetColor(0, 0, 0), "�X�R�A:%d", score);
}

// �����蔻��
void StageOne::Collision()
{
	// ����
	CollisionTemplate(0);
	// �E��
	CollisionTemplate(1);
}

// �X�R�A���Z
void StageOne::ScoreAddition()
{
	// ����
	ScoreAdditionTemplate(0);
	// �E��
	ScoreAdditionTemplate(1);
}

// �����蔻��̃e���v���[�g
void StageOne::CollisionTemplate(unsigned int number)
{
	// ��Ƀp�[�c��u���Ă��Ȃ��Ƃ��A�����蔻�肪�쓮
	if (drawFlag[number] == 0) {
		// �}�E�X���N���b�N���Ă��Ȃ��Ƃ��A�p�[�c�𗣂�
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = 0;
		}
		// �p�[�c�ƃ}�E�X�̓����蔻��
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
				catchFlag[number] = 1;
			}
		}
		// �p�[�c��͂�ł���Ƃ��A�}�E�X�ɒǔ�����
		if (catchFlag[number] == 1) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// ��ƃp�[�c�̓����蔻��
		if (PlatePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < PlatePosition.x + 512 &&
			PlatePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < PlatePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = 1;
			}
		}
	}
}

// �X�R�A���Z�̃e���v���[�g
void StageOne::ScoreAdditionTemplate(unsigned int number)
{
	// ��Ƀp�[�c��u������A�X�R�A�𔻒肷��
	if (scoreFlag[number] == 0 && drawFlag[number] == 1) {
		if (PerfectPartsPosition[number].x - judge[0] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[0] &&
			PerfectPartsPosition[number].y - judge[0] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[0]) {
			score += 50;
		}
		else if (PerfectPartsPosition[number].x - judge[1] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[1] &&
			PerfectPartsPosition[number].y - judge[1] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[1]) {
			score += 40;
		}
		else if (PerfectPartsPosition[number].x - judge[2] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[2] &&
			PerfectPartsPosition[number].y - judge[2] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[2]) {
			score += 30;
		}
		else if (PerfectPartsPosition[number].x - judge[3] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[3] &&
			PerfectPartsPosition[number].y - judge[3] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[3]) {
			score += 20;
		}
		else if (PerfectPartsPosition[number].x - judge[4] < PartsPosition[number].x &&
			PartsPosition[number].x < PerfectPartsPosition[number].x + judge[4] &&
			PerfectPartsPosition[number].y - judge[4] < PartsPosition[number].y &&
			PartsPosition[number].y < PerfectPartsPosition[number].y + judge[4]) {
			score += 10;
		}
		scoreFlag[number] = 1;
	}
}

// ���Z�b�g
void StageOne::Reset()
{
	score = 0;
	alpha = 0;	
	for (int i = 0; i < partsNumber; i++) {
		catchFlag[i] = 0;
		drawFlag[i] = 0;
		scoreFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}