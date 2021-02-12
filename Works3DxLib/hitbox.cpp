#include "hitbox.hpp"

VOID MAP_HITBOX::RESIZING_HITBOX(int TATE_MAX,int YOKO_MAX)
{
	Hitmap.resize(TATE_MAX, vector<RECT>(YOKO_MAX));
	return;
}

BOOL MAP_HITBOX::MY_CHECK_MAP1_PLAYER_COLL(RECT playercoll,int TATE_MAX,int YOKO_MAX,int& gamescene)
{
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(playercoll, this->Hitmap[tate][yoko]) == TRUE)
			{
				if (this->map[tate][yoko] == HitObj)//壁の時
				{
					return TRUE;
				}
				if (this->map[tate][yoko] == MVMapHitObj)//フロア移動の時
				{
					gamescene = GAME_LOAD_MAP_SCENE;
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
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
};

BOOL MAP_HITBOX::SETTING_HITBOX(int chipwidth, int chipheight,int Stx,int Sty
	,int TATE_MAX,int YOKO_MAX)//マップへの当たり判定の設定
{
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			this->Hitmap[tate][yoko].left = (yoko + 0) * chipwidth + 1 - Stx;
			this->Hitmap[tate][yoko].top = (tate + 0) * chipheight + 1 - Sty;
			this->Hitmap[tate][yoko].right = (yoko + 1) * chipwidth - 1 - Stx;
			this->Hitmap[tate][yoko].bottom = (tate + 1) * chipheight - 1 - Sty;
		}
	}
	return TRUE;
}

BOOL MAP_HITBOX::SETTING_HITBOX_COORDINATES(int chipwidth, int chipheight
	, int TATE_MAX, int YOKO_MAX,int CHANGEMAP)//マップへの当たり判定の設定
{
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			if (kind[tate][yoko] == CHANGEMAP)
			{
				this->Hitmap[tate][yoko].left = x[tate][yoko];
				this->Hitmap[tate][yoko].top = y[tate][yoko]+chipwidth-1;
				this->Hitmap[tate][yoko].right = x[tate][yoko] + chipwidth;
				this->Hitmap[tate][yoko].bottom = y[tate][yoko] +chipwidth;
			}
			else {
				this->Hitmap[tate][yoko].left = x[tate][yoko];
				this->Hitmap[tate][yoko].top = y[tate][yoko];
				this->Hitmap[tate][yoko].right = x[tate][yoko] + chipwidth;
				this->Hitmap[tate][yoko].bottom = y[tate][yoko] + chipheight;
			}
		}
	}
	return TRUE;
}

BOOL MAP_ENEMY::ENEMY_FLAG_RIZE()//敵に会うフラグを上昇させる
{
	flagPT += GetRand(10);
	if (flagPT > flagMAX)
	{
		flagPT = 0;
		return TRUE;
	}
	else { return FALSE; }
}

BOOL MAP_ENEMY::ENEMY_FLAG_BOSS()//敵に会うフラグを上昇させる
{
	flagPT += GetRand(10);
	if (flagPT > flagMAX)
	{
		flagPT = 0;
		return TRUE;
	}
	else { return FALSE; }
}

int MAP_ENEMY::MY_CHECK_ENEMY_PLAYER_COLL(RECT playercoll,int TATE_MAX,int YOKO_MAX)//エネミーマップとの当たり判定
{
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(playercoll, this->Hitmap[tate][yoko]) == TRUE)
			{
				if (this->map[tate][yoko] == HitObj)//草原の時
				{
					if (ENEMY_FLAG_RIZE() == TRUE)
					{
						return 1;
					}
				}
				if (this->map[tate][yoko] == HitObjBoss)//草原の時
				{
						return 2;
				}
			}
		}
	}
	return 0;
}