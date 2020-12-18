#pragma once
#include <iostream>

class BATTLE_SYSTEM
{
private:
public:
	int damage = 0;
	int DAMAGE_CALC(int, int,int&,float);
};

int BATTLE_SYSTEM::DAMAGE_CALC(int kougeki, int bougyo,int& HP,float core)
{
	damage = (int)((kougeki ^ 2) / (kougeki + bougyo)*core);
	HP - damage;
	if (HP < 0)
	{
		HP = 0;
		return 1;
	}
	return 0;
}