#include "StageTwo.h"

// �R���X�g���N�^
StageTwo::StageTwo()
{
}

// �f�X�g���N�^
StageTwo::~StageTwo()
{
	DeleteGraph(plate);
	DeleteGraph(hand1);
	DeleteGraph(hand2);
	for (int i = 0; i < partsNumber; i++) {
		DeleteGraph(parts[i]);
	}
}

// ������
void StageTwo::Initialize()
{
	// �摜�Ȃǂ̃��\�[�X�f�[�^�̓ǂݍ���
	plate = LoadGraph("Resources/okame/plate.png");
	hand1 = LoadGraph("Resources/hand1.png");
	hand2 = LoadGraph("Resources/hand2.png");
	parts[0] = LoadGraph("Resources/okame/LeftEye.png");
	parts[1] = LoadGraph("Resources/okame/RightEye.png");
	parts[2] = LoadGraph("Resources/okame/mouth.png");
	parts[3] = LoadGraph("Resources/okame/LeftCheek.png");
	parts[4] = LoadGraph("Resources/okame/RightCheek.png");
	parts[5] = LoadGraph("Resources/okame/nose.png");
	parts[6] = LoadGraph("Resources/okame/LeftEyebrows.png");
	parts[7] = LoadGraph("Resources/okame/RightEyebrows.png");
}

// �X�V
void StageTwo::Update()
{
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MousePosition.x, &MousePosition.y);

	for (int i = 0; i < partsNumber; i++) {
		// �����蔻��
		Collision(i);
		// �X�R�A���Z
		ScoreAddition(i);
		// �p�[�c����
		PartsLost(i);
	}

	// ���ʔ��\
	if (DrawCheck() == true && alpha < 255) {
		alpha += 3;
	}

#ifdef _DEBUG
	// �`�[�g
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
		for (int i = 0; i < partsNumber; i++) {
			PartsPosition[i] = PerfectPartsPosition[i];
		}
	}
#endif
}

// �`��
void StageTwo::Draw()
{
	// �v���[�g
	DrawGraph(PlatePosition.x, PlatePosition.y, plate, TRUE);

	// �A���t�@�u�����h
	if (DrawCheck() == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}

	// �p�[�c
	for (int i = 0; i < partsNumber; i++) {
		if (drawFlag[i] == false || DrawCheck() == true && alpha < 255 ||
			alpha == 255 && (GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) {
			DrawGraph(PartsPosition[i].x, PartsPosition[i].y, parts[i], TRUE);
		}
	}

	// ��
	if (alpha == 0) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand1, TRUE);
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			DrawGraph(MousePosition.x - 32, MousePosition.y - 32, hand2, TRUE);
		}
	}

	// �X�R�A
	if (alpha == 255) {
		// �X�R�A
		DrawFormatString(0, 0, GetColor(0, 0, 0), "�X�R�A:%d", (int)score);
		// �E�N���b�N�Ō��̊G�Ɣ�r
		DrawFormatString(0, 20, GetColor(0, 0, 0), "�E�N���b�N�Ō��̊G�Ɣ�r");
	}
}

// �����蔻��
void StageTwo::Collision(unsigned int number)
{
	// ��Ƀp�[�c��u���Ă��Ȃ��Ƃ��A�����蔻�肪�쓮
	if (drawFlag[number] == false) {
		// �}�E�X���N���b�N���Ă��Ȃ��Ƃ��A�p�[�c�𗣂�
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = false;
		}
		// �p�[�c�ƃ}�E�X�̓����蔻��
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && CatchCheck() == true) {
				catchFlag[number] = true;
			}
		}
		// �p�[�c��͂�ł���Ƃ��A�}�E�X�ɒǔ�����
		if (catchFlag[number] == true) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// ��ƃp�[�c�̓����蔻��
		if (PlatePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < PlatePosition.x + 512 &&
			PlatePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < PlatePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = true;
			}
		}
	}
}

// �X�R�A���Z
void StageTwo::ScoreAddition(unsigned int number)
{
	// ��Ƀp�[�c��u������A�X�R�A�𔻒肷��
	if (scoreFlag[number] == false && drawFlag[number] == true) {
		if (PartsCollisionCheck(number, 0) == true) {
			score += 12.5f;
		}
		else if (PartsCollisionCheck(number, 1) == true) {
			score += 10.0f;
		}
		else if (PartsCollisionCheck(number, 2) == true) {
			score += 7.5f;
		}
		else if (PartsCollisionCheck(number, 3) == true) {
			score += 5.0f;
		}
		else if (PartsCollisionCheck(number, 4) == true) {
			score += 2.5f;
		}
		scoreFlag[number] = true;
	}
}

// �p�[�c����
void StageTwo::PartsLost(unsigned int number)
{
	// �p�[�c����ʊO�ɏo����A�����ʒu�ɖ߂�
	if (PartsPosition[number].x < -64 || 1216 < PartsPosition[number].x ||
		PartsPosition[number].y < -64 || 656 < PartsPosition[number].y) {
		PartsPosition[number] = DefaultPartsPosition[number];
		catchFlag[number] = false;
	}
}

// ���Z�b�g
void StageTwo::Reset()
{
	score = 0;
	alpha = 0;
	for (int i = 0; i < partsNumber; i++) {
		catchFlag[i] = false;
		drawFlag[i] = false;
		scoreFlag[i] = false;
		PartsPosition[i] = DefaultPartsPosition[i];
	}
}

// �p�[�c�̓����蔻����`�F�b�N
bool StageTwo::PartsCollisionCheck(unsigned int number, unsigned int number2)
{
	if (PerfectPartsPosition[number].x - judge[number2] < PartsPosition[number].x &&
		PartsPosition[number].x < PerfectPartsPosition[number].x + judge[number2] &&
		PerfectPartsPosition[number].y - judge[number2] < PartsPosition[number].y &&
		PartsPosition[number].y < PerfectPartsPosition[number].y + judge[number2]) {
		return true;
	}
	else {
		return false;
	}
}

// �p�[�c�����Ă��邩���`�F�b�N
bool StageTwo::CatchCheck()
{
	if (catchFlag[0] == false && catchFlag[1] == false && catchFlag[2] == false && catchFlag[3] == false &&
		catchFlag[4] == false && catchFlag[5] == false && catchFlag[6] == false && catchFlag[7] == false) {
		return true;
	}
	else {
		return false;
	}
}

// �p�[�c���S�ĕ��ׂ�ꂽ�����`�F�b�N
bool StageTwo::DrawCheck()
{
	if (drawFlag[0] == true && drawFlag[1] == true && drawFlag[2] == true && drawFlag[3] == true &&
		drawFlag[4] == true && drawFlag[5] == true && drawFlag[6] == true && drawFlag[7] == true) {
		return true;
	}
	else {
		return false;
	}
}