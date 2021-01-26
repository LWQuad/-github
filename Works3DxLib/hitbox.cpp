#include "hitbox.hpp"

VOID MAP_HITBOX::RESIZING_HITBOX(int TATE_MAX,int YOKO_MAX)
{
	Hitmap.resize(TATE_MAX+1, vector<RECT>(YOKO_MAX+1));
	return;
}

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
			this->Hitmap[tate][yoko].left = (yoko + 0) * chipwidth + 1 - 10 * chipwidth;
			this->Hitmap[tate][yoko].top = (tate + 0) * chipheight + 1 - 20 * chipheight;
			this->Hitmap[tate][yoko].right = (yoko + 1) * chipwidth - 1 - 10 * chipwidth;
			this->Hitmap[tate][yoko].bottom = (tate + 1) * chipheight - 1 - 20 * chipheight;
		}
	}
	return TRUE;
}

BOOL MAP_ENEMY::ENEMY_FLAG_RIZE()//�G�ɉ�t���O���㏸������
{
	flagPT += GetRand(10);
	if (flagPT > flagMAX)
	{
		flagPT = 0;
		return TRUE;
	}
	else { return FALSE; }
}

int MAP_ENEMY::MY_CHECK_ENEMY_PLAYER_COLL(RECT playercoll)//�G�l�~�[�}�b�v�Ƃ̓����蔻��
{
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(playercoll, this->Hitmap[tate][yoko]) == TRUE)
			{
				if (this->map[tate][yoko] == 191)//�����̎�
				{
					if (ENEMY_FLAG_RIZE() == TRUE)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}