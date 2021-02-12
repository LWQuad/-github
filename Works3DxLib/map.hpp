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

#define ERROR_MESSAGE TEXT("�G���[����")

#define MAP_TAG_1 TEXT(".\\SAVEDATA\\SAVESLOT01\\maptag.csv")
#define MAP_SAVE_PLACE_X_1 TEXT(".\\SAVEDATA\\SAVESLOT01\\���WX.csv")
#define MAP_SAVE_PLACE_Y_1 TEXT(".\\SAVEDATA\\SAVESLOT01\\���WY.csv")

#define MAP_TAG_2 TEXT(".\\SAVEDATA\\SAVESLOT02\\maptag.csv")
#define MAP_TAG_3 TEXT(".\\SAVEDATA\\SAVESLOT03\\maptag.csv")


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

#define MAP_FOREST_SAVE_PLACE_X TEXT(".\\MAP\\FOREST\\forest_���WX.csv")
#define MAP_FOREST_SAVE_PLACE_Y TEXT(".\\MAP\\FOREST\\forest_���WY.csv")


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
	int MAPtag[3] = { 0 };
	BOOL LOADING_MAP(const char*);//�}�b�v��ǂݍ��ށi�}�b�v�̃p�X�j
	BOOL SAVE_MAP(int,int,const char*,const char*,const char*);
	BOOL LOADING_MAP_COORDINATES(const char*,const char*);
	BOOL LOADING_MAP_TAG(int,const char*);
	BOOL isVIEW;//�\���ł��邩������
	VOID RESIZE(int, int);
    void MAPSETTING(int,int,int,int,int,int);//�}�b�v�̍��W�������Z�b�g����i�}�b�v�`�b�v�̕��A����,�����ʒux,y�j
	vector<vector<int>> kind, width, height, x,y , mapF, map;
	/*-					���,���@�@�����@x,y���W�@�}�b�v�̏������p-*/
	VOID INTARACTIV_MAP(int,int);
	int mapmove=0;
};




