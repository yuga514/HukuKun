#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageOne
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageOne();

	// �f�X�g���N�^
	~StageOne();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �����蔻��
	void Collision();

	// �X�R�A���Z
	void ScoreAddition();

	// �����蔻��̃e���v���[�g
	void CollisionTemplate(unsigned int number);

	// �X�R�A���Z�̃e���v���[�g
	void ScoreAdditionTemplate(unsigned int number);

	// ���Z�b�g
	void Reset();

	// �X�R�A�̎擾
	unsigned int GetScore() { return score; }

	// �A���t�@�l�̎擾
	unsigned int GetAlpha() { return alpha; }

private: // �����o�ϐ�
	const unsigned int judge[5] = { 7,14,21,28,35 };
	const unsigned int partsNumber = 5;
	unsigned int score = 0;
	unsigned int alpha = 0;
	bool catchFlag[5] = {};
	bool drawFlag[5] = {};
	bool scoreFlag[5] = {};

	const XMINT2 PerfectPartsPosition[5] = { { 480,200 }, { 672,200 } };
	XMINT2 PartsPosition[5] = { { 100,100 }, { 100,500 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
	int plate = 0;
	int hand1 = 0;
	int hand2 = 0;
	int parts[5] = {};
};