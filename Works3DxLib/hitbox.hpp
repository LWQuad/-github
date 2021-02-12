#pragma once
#include <iostream>
#include "DxLib.h"
#include "windowsystem.h"
#include <vector>
#include "map.hpp"
using namespace std;

//当たり判定のある場所
#define MAP_SAMPLE_HITOBJ 63
#define MAP_MURA_HITOBJ 1415
#define MAP_FOREST_HITOBJ 1415

#define MAP_FOREST_HITOBJ_BOSS 1541

//マップ移動の当たり判定
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
	int HitObj;		//ぶつかるものの番号を格納
	int MVMapHitObj; //マップを移動する番号当たり判定の番号を格納
};

//敵が出現する場所
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

