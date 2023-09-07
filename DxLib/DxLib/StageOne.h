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

	// �����蔻��̃e���v���[�g
	void CollisionTemplate(unsigned int number);

	// ���Z�b�g
	void Reset();

	// �l�N�X�g�V�[���t���O�̎擾
	unsigned int GetNextSceneFlag() { return nextSceneFlag; }

private: // �����o�ϐ�
	unsigned int alpha = 0;
	unsigned int score = 0;
	unsigned int number = 2;
	bool catchFlag[2] = {};
	bool drawFlag[2] = {};
	bool scoreFlag[2] = {};
	bool nextSceneFlag = 0;

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