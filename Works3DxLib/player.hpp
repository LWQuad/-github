#pragma once
#include "image.hpp"
class CHARA //�L�����N�^�[�̃N���X
{
public:
	LOAD_SINGLE_IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY
	int OldX;					//�ړ��O��X���W
	int OldY;					//�ړ��O��Y���W
	int OldCenterX;
	int OldCenterY;

	//MUSIC musicShot;			//�v���C���[�̔��ˉ�

	//BOOL CanShot;				//�V���b�g�ł��邩
	//int ShotReLoadCnt;			//�V���b�g�����[�h����
	//int ShotReLoadCntMAX;		//�V���b�g�����[�h����(MAX)

	//TAMA tama[TAMA_MAX];		//�V���b�g����e

	RECT coll;					//�����蔻��
	//iPOINT collBeforePt;		//������O�̍��W

};	//�L�����N�^�[�\����

