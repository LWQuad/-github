#pragma once
#include <iostream>
#include "DxLib.h"
#include "image.hpp"
#include "music.hpp"

class BATTLE_UI
{
private:
	int KOUGEKI = 0;
	int SKILL = 1;
	int GUARD = 2;
	int ITEM = 3;
	int RUN = 4;//項目移動するタグ
	int countMAX = 20;
	int ScountMAX = 30;
	int IAICountMAX = 30;

public:
	int SpotUIx = 15;
	int NonSpotUIx = 30;
	LOAD_SINGLE_IMAGE image;
	int count = 0;
	int UItag = 0;//UIの項目を管理する
	int UIx[5] = { 30,30,30,30,30 };
	int BrightR = 255, BrightG = 255, BrightB = 255;//画面の輝度用カラー初期設定
	int BrightMAX = 255;
	int Mssgcount = 0;
	int MssgcntMx = 90;
	int Defcount = 0;
	int DefcntMx = 90;
	int Expcount = 0;
	int ExpcntMx = 90;
	int Skilltag = 0;
	int SkilltagIAI = 0;
	int Scount = 0;
	int cricnt = 0;
	int Endefeatcnt = 0;
	BOOL PlusEXPflg = TRUE;
	BOOL LvUPflg = TRUE;
	//スキルの描画場所を示す
	float Iaix = 480, Iaiy = 400, Iaix2 = 710, Iaiy2 = 490;//居合の描画場所
	float Iaiy2Move = (490 - 430) / 30; int IaiCount = 0;
	float KiKonx = 720, KiKony = 400, KiKonx2 = 950, KiKony2 = 490;//輝魂
	float KiKony2Move = (490 - 430) / 30, KiKonxMove = (720 - 480) / 30,
		KiKonx2Move = (950 - 710) / 30;
	float Kenx = 480, Keny = 500, Kenx2 = 710, Keny2 = 590;//剣術
	float KenyMove = (500 - 400) / 30, Keny2Move = (590 - 430) / 30;
	float Magicx = 720, Magicy = 500, Magicx2 = 950, Magicy2 = 590;
	float MagicxMove = (720 - 480) / 30, MagicyMove = (500 - 400) / 30,
		Magicx2Move = (950 - 710) / 30, Magicy2Move = (590 - 430) / 30;
	int SnameIAI, SnameKiKon, SnameKen, SnameMagic;

	int Iaiskillx = 480, Iaiskilly = 435, Iaiskillx2 = 940, Iaiskilly2 = 460;
	//バトルスキルの要素を収容する変数
	MUSIC skillSE;

	int ItemPosX = 480, ItemPosY = 400;
	int ICarsolX = ItemPosX - 2, ICarsolY = ItemPosY - 2, ICarsolX2 = ItemPosX + 210+2, ICarsolY2 = ItemPosY + 22;
	int ItemBrend = 200;
	BOOL ItemBrendflg = TRUE;
	int Itemtag = 0;

	BOOL EncntUIisView = TRUE;
	BOOL CHANGE_COUNT();
	BOOL ENTER_COUNT_SKILL();
	BOOL SKILL_MOVE();
	VOID SKILL_MOVE_NEW();//スキル項目の描画位置を初期化する関数

	VOID ChengingBrend_Item();
};

BOOL BATTLE_UI::CHANGE_COUNT()//UIの項目移動を待つ関数
{
	count++;
	if (count > countMAX)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL BATTLE_UI::ENTER_COUNT_SKILL()//UIの項目移動を待つ関数
{
	Scount++;
	if (Scount > ScountMAX)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL BATTLE_UI::SKILL_MOVE()//UIの項目移動を待つ関数
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

VOID BATTLE_UI::ChengingBrend_Item()
{
	if (ItemBrendflg == TRUE)
	{
		ItemBrend -= 5;
	}
	if (ItemBrendflg == FALSE)
	{
		ItemBrend += 5;
	}
	if (ItemBrend <= 0)
	{
		ItemBrendflg = FALSE;
	}
	if (ItemBrend >= 200)
	{
		ItemBrendflg = TRUE;
	}
}