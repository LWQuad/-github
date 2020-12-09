#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "windowsystem.h"
#include "DxLib.h"
#include <string>


#define GAME_MAP_PATH1 TEXT(".\\IMAGEs\\MAPIMAGE\\mapchip1.png")
#define GAME_MAP1_UNDER_TXT TEXT(".\\MAP\\map1_�}�b�v��.txt")
#define GAME_MAP1_MIDDLE_TXT TEXT(".\\MAP\\map1_�}�b�v��.txt")
#define GAME_MAP1_ON_TXT TEXT(".\\MAP\\map1_�}�b�v��.txt")
#define GAME_MAP1_HITBOX TEXT(".\\MAP\\map1_�����蔻��̃}�b�v.txt")

#define MAP_DIV_WIDTH		32	//�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT		32	//�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE		32	//�摜���c�ɕ������鐔
#define MAP_DIV_YOKO		41	//�摜�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�摜�𕪊����鑍��
#define MAP_TATE_MAX1		40
#define MAP_YOKO_MAX1		40
using namespace std;

class MAP_DIV//�}�b�v�`�b�v�摜���Ǘ�����֐�
{
public:
	int handle[MAP_DIV_NUM];			//���������摜�n���h�����擾
	int kind[MAP_DIV_NUM];				//�}�b�v�̎��
	int width;							//��
	int height;							//��

	BOOL DIV_MAP();
};

class MAPINPUT //�}�b�v��ǂݍ��ރN���X
{
public:
	int kind[MAP_TATE_MAX1][MAP_YOKO_MAX1];				//�}�b�v�̎��
	int width[MAP_TATE_MAX1][MAP_YOKO_MAX1];							//��
	int height[MAP_TATE_MAX1][MAP_YOKO_MAX1];							//��
	int x[MAP_TATE_MAX1][MAP_YOKO_MAX1];
	int y[MAP_TATE_MAX1][MAP_YOKO_MAX1];
	int mapF[MAP_TATE_MAX1][MAP_YOKO_MAX1];//�}�b�v�f�[�^���i�[����񎟌��z��
	int map[MAP_TATE_MAX1][MAP_YOKO_MAX1];//�}�b�v�f�[�^���i�[����񎟌��z��
	BOOL LOADING_MAP(const char*);
	BOOL isVIEW;//�\���ł��邩������
    void MAPSETTING(int,int);

};




