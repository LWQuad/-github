#pragma once
#include <iostream>
#include "DxLib.h"
#include "playerstatas.hpp"

#define ENEMY_STATES_GLASS1 TEXT(".\\STATES\\EnemyStates.csv")

class EnemyStates :public PlayerStates
{
public:
	int enemy_tag[10];
};

