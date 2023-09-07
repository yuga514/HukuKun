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

	// ���ʔ��\
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		if (alpha < 255) {
			alpha += 3;
		}
	}

	if (380 < PartsPosition[0].x && PartsPosition[0].x < 580 &&
		100 < PartsPosition[0].y && PartsPosition[0].y < 300 && scoreFlag[0] == 0 && drawFlag[0] == 1) {
		score += 50;
		scoreFlag[0] = 1;
	}
	if (572 < PartsPosition[1].x && PartsPosition[1].x < 772 &&
		100 < PartsPosition[1].y && PartsPosition[1].y < 200 && scoreFlag[1] == 0 && drawFlag[1] == 1) {
		score += 50;
		scoreFlag[1] = 1;
	}

	// ���̃V�[���ւ̃t���O���I���ɂ���
	if (alpha == 255) {
		nextSceneFlag = 1;
	}	
}

// �`��
void StageOne::Draw()
{
	// ��
	DrawGraph(FacePosition.x, FacePosition.y, face, TRUE);

	// ��
	if (drawFlag[0] == 0) {
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
	}
	if (drawFlag[1] == 0) {
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);
	}

	// ���ʔ��\
	if (drawFlag[0] == 1 && drawFlag[1] == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(PartsPosition[0].x, PartsPosition[0].y, eye1, TRUE);
		DrawGraph(PartsPosition[1].x, PartsPosition[1].y, eye2, TRUE);
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

// �����蔻��̃e���v���[�g
void StageOne::CollisionTemplate(unsigned int number)
{
	// ���ڂ̓����蔻��
	if (drawFlag[number] == 0) {
		// �}�E�X���N���b�N���Ă��Ȃ��Ƃ��A�p�[�c�𗣂�
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			catchFlag[number] = 0;
		}
		// ���ڂ̃p�[�c�̓����蔻��
		if (PartsPosition[number].x < MousePosition.x && MousePosition.x < PartsPosition[number].x + 128 &&
			PartsPosition[number].y < MousePosition.y && MousePosition.y < PartsPosition[number].y + 128) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && catchFlag[0] == 0 && catchFlag[1] == 0) {
				catchFlag[number] = 1;
			}
		}
		// ���ڂ�͂�ł���Ƃ��A�}�E�X�ɒǔ�����
		if (catchFlag[number] == 1) {
			PartsPosition[number].x = MousePosition.x - 64;
			PartsPosition[number].y = MousePosition.y - 64;
		}
		// ���ڂ̃p�[�c�Ɗ�̓����蔻��
		if (FacePosition.x < PartsPosition[number].x + 128 && PartsPosition[number].x < FacePosition.x + 512 &&
			FacePosition.y < PartsPosition[number].y + 128 && PartsPosition[number].y < FacePosition.y + 512) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
				drawFlag[number] = 1;
			}
		}
	}
}

// ���Z�b�g
void StageOne::Reset()
{
	for (int i = 0; i < number; i++) {
		catchFlag[i] = 0;
	}
	PartsPosition[0] = { 100,100 };
	PartsPosition[1] = { 100,500 };
}