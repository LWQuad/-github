#pragma once
#include <iostream>
#include "DxLib.h"
#include "windowsystem.h"
#include "map.hpp"
class MAP_HITBOX:public MAPINPUT
{
public:
	BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
	BOOL MY_CHECK_RECT_COLL(RECT, RECT);
	BOOL SETTING_HITBOX(int, int);
	RECT Hitmap[MAP_TATE_MAX1][MAP_YOKO_MAX1];
};

class MAP_ENEMY :public MAP_HITBOX
{
private:
	int flagMAX = 800;
public:
	int flagPT=0;
	int MY_CHECK_ENEMY_PLAYER_COLL(RECT);
	BOOL ENEMY_FLAG_RIZE();
};

