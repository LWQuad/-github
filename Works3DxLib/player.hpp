#pragma once
#include "image.hpp"
class CHARA //�L�����N�^�[�̃N���X
{
public:
	//LOAD_SINGLE_IMAGE image;				//IMAGE�\����
	LOAD_DIV_IMAGE image;
	int speed;					//����
	int OldX;					//�ړ��O��X���W
	int OldY;					//�ړ��O��Y���W
	int Nowhandle=0;				//���݂̉摜�̃n���h��
	RECT coll;					//�����蔻��

};

