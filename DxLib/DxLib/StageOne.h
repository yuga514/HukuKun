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

	// ���Z�b�g
	void Reset();

private: // �����o�ϐ�
	bool catchFlag[2] = {};

	XMINT2 MousePosition = {};
	XMINT2 PartsPosition[2] = { { 100,100 }, { 100,500 } };

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
	int face = LoadGraph("Resources/sampleface2.png");
	int hand1 = LoadGraph("Resources/hand1.png");
	int hand2 = LoadGraph("Resources/hand2.png");
	int eye1 = LoadGraph("Resources/eye1.png");
	int eye2 = LoadGraph("Resources/eye2.png");
};