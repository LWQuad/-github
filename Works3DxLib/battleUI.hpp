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
	int ScountMAX = 30;
	int IAICountMAX = 30;

public:
	int SpotUIx = 15;
	int NonSpotUIx = 30;
	LOAD_SINGLE_IMAGE image;
	int count = 0;
	int UItag = 0;//UI‚Ì€–Ú‚ðŠÇ—‚·‚é
	int UIx[5] = { 30,30,30,30,30 };
	int BrightR = 255, BrightG = 255, BrightB = 255;//‰æ–Ê‚Ì‹P“x—pƒJƒ‰[‰ŠúÝ’è
	int BrightMAX = 255;
	int Mssgcount = 0;
	int MssgcntMx = 90;
	int Defcount = 0;
	int DefcntMx = 90;
	int Expcount = 0;
	int ExpcntMx = 90;
	int Skilltag = 0;
	int Scount = 0;
	int cricnt = 0;
	int Endefeatcnt = 0;
	BOOL PlusEXPflg = TRUE;
	BOOL LvUPflg = TRUE;
	//ƒXƒLƒ‹‚Ì•`‰æêŠ‚ðŽ¦‚·
	float Iaix = 480, Iaiy = 400, Iaix2 = 710, Iaiy2 = 490;//‹‡‚Ì•`‰æêŠ
	float Iaiy2Move = (490 - 430) / 30; int IaiCount = 0;
	float KiKonx = 720, KiKony = 400, KiKonx2 = 950, KiKony2 = 490;//‹P°
	float KiKony2Move = (490 - 430) / 30, KiKonxMove = (720 - 480) / 30,
		KiKonx2Move = (950 - 710) / 30;
	float Kenx = 480, Keny = 500, Kenx2 = 710, Keny2 = 590;//Œ•p
	float KenyMove = (500 - 400) / 30, Keny2Move = (590 - 430) / 30;
	float Magicx = 720, Magicy = 500, Magicx2 = 950, Magicy2 = 590;
	float MagicxMove = (720 - 480) / 30, MagicyMove = (500 - 400) / 30,
		Magicx2Move = (950 - 710) / 30, Magicy2Move = (590 - 430) / 30;
	int SnameIAI, SnameKiKon, SnameKen, SnameMagic;
	BOOL EncntUIisView = TRUE;
	BOOL CHANGE_COUNT();
	BOOL ENTER_COUNT_SKILL();
	BOOL SKILL_MOVE();
	VOID SKILL_MOVE_NEW();//ƒXƒLƒ‹€–Ú‚Ì•`‰æˆÊ’u‚ð‰Šú‰»‚·‚éŠÖ”
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

BOOL BATTLE_UI::ENTER_COUNT_SKILL()//UI‚Ì€–ÚˆÚ“®‚ð‘Ò‚ÂŠÖ”
{
	Scount++;
	if (Scount > ScountMAX)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL BATTLE_UI::SKILL_MOVE()//UI‚Ì€–ÚˆÚ“®‚ð‘Ò‚ÂŠÖ”
{
	IaiCount++;
	if (IaiCount > IAICountMAX)
	{
		return FALSE;
	}
	return TRUE;
}

VOID BATTLE_UI::SKILL_MOVE_NEW()
{
	Iaix = 480, Iaiy = 400, Iaix2 = 710, Iaiy2 = 490;
	KiKonx = 720, KiKony = 400, KiKonx2 = 950, KiKony2 = 490;
	Kenx = 480, Keny = 500, Kenx2 = 710, Keny2 = 590;
	Magicx = 720, Magicy = 500, Magicx2 = 950, Magicy2 = 590;
	IaiCount = 0;
}
