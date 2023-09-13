#pragma once

#include "DxLib.h"
#include <DirectXMath.h>

using namespace DirectX;

class StageFour
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageFour();

	// �f�X�g���N�^
	~StageFour();

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
	const int partsNumber = 10;
	float score = 0;
	unsigned int alpha = 0;
	bool catchFlag[10] = {};
	bool drawFlag[10] = {};
	bool scoreFlag[10] = {};

	const XMINT2 PerfectPartsPosition[10] = { { 502,300 }, { 650,300 }, { 575,434 }, { 464,198 }, { 687,182 },
												{ 567,373 }, { 496,247 }, { 648,240 }, { 377,158 }, { 787,158 } };
	const XMINT2 DefaultPartsPosition[10] = { { 100,100 }, { 100,300 }, { 100,500 }, { 200,200 }, { 200,400 },
												{ 952,100 }, { 952,300 }, { 952,500 }, { 1052,200 }, { 1052,400 } };
	XMINT2 PartsPosition[10] = { { 50,50 }, { 50,250 }, { 50,450 }, { 150,150 }, { 150,350 },
									{ 1002,50 }, { 1002,250 }, { 1002,450 }, { 1102,150 }, { 1102,350 } };
	XMINT2 MousePosition = {};
	XMINT2 PlatePosition = { 384,104 };

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
	int hand1 = 0;
	int hand2 = 0;
	int plate = 0;
	int parts[10] = {};
};