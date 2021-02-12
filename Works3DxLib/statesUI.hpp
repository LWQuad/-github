#pragma once
#include "image.hpp"
#include "DxLib.h"

class STATES_UI
{
private:

public:
	LOAD_SINGLE_IMAGE charaimg, UIimg, back, back2;
	int Ctag = 0;
	int Savetag = 0, SavingStch = 0;
	int CataEndtag = 0;
	//ステータス画面のステータス位置
	int STallx = 50;
	int StatusX = 10, UIY = 15, StatusX2 = 230, UIY2 = 70,
		ItemX = 250, ItemX2 = 470, SaveX = 490, SaveX2 = 710,
		LoadX = 730, LoadX2 = 950;
	int CarsolX=StatusX, CarsolY=UIY, CarsolX2=StatusX2, CarsolY2=UIY2;
	//ステータス画面のアイテム位置
	int ItemPosX = 50, ItemPosY = 100;
	int ICarsolX = ItemPosX-5, ICarsolY = ItemPosY-5, ICarsolX2 = ItemPosX+275, ICarsolY2 = ItemPosY+25;
	int ItemBrend = 200;
	BOOL ItemBrendflg = TRUE;
	VOID ChengingBrend_Item();
	int Itemtag = 0;
};

VOID STATES_UI::ChengingBrend_Item()
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



