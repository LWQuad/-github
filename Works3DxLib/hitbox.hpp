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

BOOL MAP_HITBOX::MY_CHECK_MAP1_PLAYER_COLL(RECT playercoll)
{
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(playercoll, this->Hitmap[tate][yoko]) == TRUE)
			{
				if (this->map[tate][yoko] == 63)//�ǂ̎�
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
};

BOOL MAP_HITBOX::MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left <= b.right &&
		a.top <= b.bottom &&
		a.right >= b.left &&
		a.bottom >= b.top
		)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
};

BOOL MAP_HITBOX::SETTING_HITBOX(int chipwidth, int chipheight)//�}�b�v�ւ̓����蔻��̐ݒ�
{
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			this->Hitmap[tate][yoko].left = (yoko + 0) * chipwidth + 1-15 * chipwidth;
			this->Hitmap[tate][yoko].top = (tate + 0) * chipheight + 1-20 * chipheight;
			this->Hitmap[tate][yoko].right = (yoko + 1) * chipwidth - 1-15 * chipwidth;
			this->Hitmap[tate][yoko].bottom = (tate + 1) * chipheight - 1-20 * chipheight;
		}
	}
	return TRUE;
}