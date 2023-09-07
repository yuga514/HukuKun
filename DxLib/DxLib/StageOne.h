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
	XMINT2 FacePosition = { 384,104 };
	XMINT2 PartsPosition[2] = { { 100,100 }, { 100,500 } };

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾
	int face = 0;
	int hand1 = 0;
	int hand2 = 0;
	int eye1 = 0;
	int eye2 = 0;
};