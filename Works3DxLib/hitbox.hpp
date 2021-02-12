#pragma once
#include <iostream>
#include "DxLib.h"
#include "windowsystem.h"
#include <vector>
#include "map.hpp"
using namespace std;

//�����蔻��̂���ꏊ
#define MAP_SAMPLE_HITOBJ 63
#define MAP_MURA_HITOBJ 1415
#define MAP_FOREST_HITOBJ 1415

#define MAP_FOREST_HITOBJ_BOSS 1541

//�}�b�v�ړ��̓����蔻��
#define MAP_MURA_MOVE_HITOBJ 1910
#define MAP_FOREST_MOVE_HITOBJ 1960

#define MOVE_HIT_DOWN 0
#define MOVE_HIT_UP 1
#define MOVE_HIT_LEFT 2
#define MOVE_HIT_RIGHT 3


class MAP_HITBOX:public MAPINPUT
{
public:
	BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT,int,int,int&);
	BOOL MY_CHECK_RECT_COLL(RECT, RECT);
	BOOL SETTING_HITBOX(int, int,int,int,int,int);
	BOOL SETTING_HITBOX_COORDINATES(int, int, int, int,int);
	VOID RESIZING_HITBOX(int, int);
	vector<vector<RECT>> Hitmap;
	int HitObj;		//�Ԃ�����̂̔ԍ����i�[
	int MVMapHitObj; //�}�b�v���ړ�����ԍ������蔻��̔ԍ����i�[
};

//�G���o������ꏊ
#define MAP_SAMPLE_ENEMY_HITOBJ 191
#define MAP_MURA_ENEMY_HITOBJ 0
#define MAP_FOREST_ENEMY_HITOBJ 1540

class MAP_ENEMY :public MAP_HITBOX
{
private:
	int flagMAX = 800;
public:
	int flagPT=0;
	int HitObjBoss;
	int MY_CHECK_ENEMY_PLAYER_COLL(RECT,int,int);
	BOOL ENEMY_FLAG_RIZE();
	BOOL ENEMY_FLAG_BOSS();
};

