#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageTwo
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageTwo();

	// �f�X�g���N�^
	~StageTwo();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �����蔻��
	void Collision(unsigned int number);

	// �X�R�A���Z
	void ScoreAddition(unsigned int number);

	// �p�[�c����
	void PartsLost(unsigned int number);

	// ���Z�b�g
	void Reset();

	// �p�[�c�̓����蔻����`�F�b�N
	bool PartsCollisionCheck(unsigned int number, unsigned int number2);

	// �p�[�c�����Ă��邩���`�F�b�N
	bool CatchCheck();

	// �p�[�c���S�ĕ��ׂ�ꂽ�����`�F�b�N
	bool DrawCheck();

	// �X�R�A�̎擾
	float GetScore() { return score; }

	// �A���t�@�l�̎擾
	unsigned int GetAlpha() { return alpha; }

private: // �����o�ϐ�
	const int judge[5] = { 7,14,21,28,35 };
	const int partsNumber = 8;
	float score = 0.0f;
	unsigned int alpha = 0;
	bool catchFlag[8] = {};
	bool drawFlag[8] = {};
	bool scoreFlag[8] = {};

	const XMINT2 PerfectPartsPosition[8] = { { 511,268 }, { 641,268 }, { 577,405 }, { 499,346 },
												{ 653,346 }, { 576,319 }, { 516,204 }, { 636,204 } };
	const XMINT2 DefaultPartsPosition[8] = { { 50,50 }, { 50,250 }, { 150,150 }, { 150,350 },
												{ 1002,50 }, { 1002,250 }, { 1102,150 }, { 1102,350 } };
	XMINT2 PartsPosition[8] = { { 50,50 }, { 50,250 }, { 150,150 }, { 150,350 },
								{ 1002,50 }, { 1002,250 }, { 1102,150 }, { 1102,350 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
	int hand1 = 0;
	int hand2 = 0;
	int plate = 0;
	int parts[8] = {};
};