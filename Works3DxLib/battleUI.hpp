#pragma once
#include <iostream>
#include "DxLib.h"
#include "image.hpp"

class BATTLE_UI
{
private:
	int KOUGEKI = 0;
	int SKILL = 1;
	int GUARD = 2;
	int ITEM = 3;
	int RUN = 4;//€–ÚˆÚ“®‚·‚éƒ^ƒO
	int countMAX = 20;

public:
	int SpotUIx = 15;
	int NonSpotUIx = 30;
	LOAD_SINGLE_IMAGE image;
	int count = 0;
	int UItag = 0;//UI‚Ì€–Ú‚ðŠÇ—‚·‚é
	int UIx[5] = { 30,30,30,30,30 };
	BOOL CHANGE_COUNT();
};

BOOL BATTLE_UI::CHANGE_COUNT()//UI‚Ì€–ÚˆÚ“®‚ð‘Ò‚ÂŠÖ”
{
	count++;
	if (count > countMAX)
	{
		return TRUE;
	}
	return FALSE;
}
