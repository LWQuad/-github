#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "windowsystem.h"
#include "DxLib.h"
#include <string>
using namespace std;

//�T���v���p
#define GAME_MAP_PATH1 TEXT(".\\IMAGEs\\MAPIMAGE\\mapchip1.png")
#define GAME_MAP1_UNDER_TXT TEXT(".\\MAP\\map1_�}�b�v��.csv")
#define GAME_MAP1_MIDDLE_TXT TEXT(".\\MAP\\map1_�}�b�v��.csv")
#define GAME_MAP1_ON_TXT TEXT(".\\MAP\\map1_�}�b�v��.csv")
#define GAME_MAP1_HITBOX TEXT(".\\MAP\\map1_�����蔻��̃}�b�v.csv")
#define GAME_MAP1_ENEMYMAP TEXT(".\\MAP\\map1_�G�̏o���}�b�v.csv")

#define MAP_TATE_MAX1		40
#define MAP_YOKO_MAX1		40
#define MAP_SAMP_STx (32*MAP_YOKO_MAX1)-GAME_WIDTH
#define MAP_SAMP_STy (32*MAP_TATE_MAX1)-GAME_HEIGHT

//���p
#define MAP_MURA_PATH TEXT(".\\MAP\\VILLAGE\\���p�^�C��.png")
#define MAP_MURA_UNDER TEXT(".\\MAP\\VILLAGE\\mura_��.csv")
#define MAP_MURA_MID TEXT(".\\MAP\\VILLAGE\\mura_��.csv")
#define MAP_MURA_ON TEXT(".\\MAP\\VILLAGE\\mura_��.csv")
#define MAP_MURA_ENEMYMAP TEXT(".\\MAP\\VILLAGE\\mura_�G�̏o���}�b�v.csv")
#define MAP_MURA_HITBOX TEXT(".\\MAP\\VILLAGE\\mura_�����蔻��̃}�b�v.csv")

#define MAP_MURA_TATEMAX	34
#define MAP_MURA_YOKOMAX	103
#define MAP_MURA_STx (32*MAP_MURA_YOKOMAX)-GAME_WIDTH
#define MAP_MURA_STy 0
#define MAP_MURA_DIV_TATE 50
#define MAP_MURA_DIV_YOKO 50

//�X�p
#define MAP_FOREST_PATH TEXT(".\\MAP\\FOREST\\�X�p�^�C��.png")
#define MAP_FOREST_UNDER TEXT(".\\MAP\\FOREST\\forest_��.csv")
#define MAP_FOREST_MID TEXT(".\\MAP\\FOREST\\forest_��.csv")
#define MAP_FOREST_ON TEXT(".\\MAP\\FOREST\\forest_��.csv")
#define MAP_FOREST_ENEMYMAP TEXT(".\\MAP\\FOREST\\forest_�G�̏o���}�b�v.csv")
#define MAP_FOREST_HITBOX TEXT(".\\MAP\\FOREST\\forest_�����蔻��̃}�b�v.csv")

#define MAP_FOREST_TATEMAX	100
#define MAP_FOREST_YOKOMAX	53
#define MAP_FOREST_STx 0
#define MAP_FOREST_STy (32*MAP_FOREST_TATEMAX)-GAME_HEIGHT
#define MAP_FOREST_DIV_TATE 50
#define MAP_FOREST_DIV_YOKO 50


#define MAP_DIV_WIDTH		32	//�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT		32	//�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE		32	//�摜���c�ɕ������鐔
#define MAP_DIV_YOKO		41	//�摜�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�摜�𕪊����鑍��

using namespace std;

class MAP_DIV//�}�b�v�`�b�v�摜���Ǘ�����֐�
{
public:
	vector<int> handle,kind;
	int width;							//��
	int height;							//��

	BOOL DIV_MAP(const char*,int,int,int);
};

class MAPINPUT //�}�b�v��ǂݍ��ރN���X
{
public:
	BOOL LOADING_MAP(const char*);//�}�b�v��ǂݍ��ށi�}�b�v�̃p�X�j
	BOOL isVIEW;//�\���ł��邩������
	VOID RESIZE(int, int);
    void MAPSETTING(int,int,int,int,int,int);//�}�b�v�̍��W�������Z�b�g����i�}�b�v�`�b�v�̕��A����,�����ʒux,y�j
	vector<vector<int>> kind, width, height, x,
		y , mapF, map;
	/*-					���,���@�@�����@x,y���W�@�}�b�v�̏������p-*/
};




