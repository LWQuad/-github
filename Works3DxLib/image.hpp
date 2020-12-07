#pragma once
#include "windowsystem.h"
#include "map.hpp"
#include <vector>

#define IMAGE_TITLE TEXT(".\\IMAGEs\\Kitune.jpg")
#define IMAGE_PLAYER_BATTLE TEXT(".\\IMAGEs\\playerimage.png")
#define IMAGE_ENEMY1 TEXT(".\\IMAGEs\\enemyimage.png")



class LOAD_SINGLE_IMAGE //�摜�ꖇ��ǂݍ��ރN���X
{
public:
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	vector<int> maphandle;		//�}�b�v�`�b�v�̃n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
	BOOL IsDraw;				//�\���̉�

	BOOL LOADING_IMAGE(const char*); //�摜��ǂݍ���(�摜�̃p�X)
};

