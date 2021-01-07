#pragma once
#include <iostream>
#include "DxLib.h"
#include "playerstatas.hpp"

#define ENEMY_STATES_GLASS1 TEXT(".\\STATES\\OkaUmiushiStates.csv")
#define ENEMY_STATES_GLASS2 TEXT(".\\STATES\\OkaUmiushiStates2.csv")
#define ENEMY_STATES_GLASS3 TEXT(".\\STATES\\OkaUmiushiStates3.csv")

class EnemyStates :public PlayerStates
{
public:
	VOID ENEMY_KIND_FLAG();//敵をランダムに選んでデータを読み込む関数
};

VOID EnemyStates::ENEMY_KIND_FLAG()
{
	int kindflag = GetRand(100);
	if (kindflag > 80)
	{
		INPUT_STATES(ENEMY_STATES_GLASS1);
		return;
	}
	else if (kindflag > 30)
	{
		INPUT_STATES(ENEMY_STATES_GLASS2);
		return;
	}
	else 
	{
		INPUT_STATES(ENEMY_STATES_GLASS3);
		return;
	}
}

