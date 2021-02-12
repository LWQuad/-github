#pragma once
#include "image.hpp"
class CHARA //キャラクターのクラス
{
private:
	int countD = 0, countU = 0, countL = 0, countR = 0;
public:
	//LOAD_SINGLE_IMAGE image;				//IMAGE構造体
	LOAD_DIV_IMAGE image;
	int speed;					//速さ
	int OldX;					//移動前のX座標
	int OldY;					//移動前のY座標
	int Nowhandle=0;				//現在の画像のハンドル
	RECT coll;					//当たり判定
	VOID MOVE_CHARA_CHIP_DOWN();
	VOID MOVE_CHARA_CHIP_UP();
	VOID MOVE_CHARA_CHIP_LEFT();
	VOID MOVE_CHARA_CHIP_RIGHT();
	int charahandle=0;
};

VOID CHARA::MOVE_CHARA_CHIP_DOWN()
{
	countD++;
	if (countD>0)
	{
		charahandle = 0;
	}
	if (countD > 7)
	{
		charahandle = 1;
	}
	if (countD > 15)
	{
		charahandle = 2;
	}
	if (countD > 22)
	{
		charahandle = 1;
	}
	if (countD > 30)
	{
		countD = 0;
	}
	return;
}

VOID CHARA::MOVE_CHARA_CHIP_UP()
{
	countU++;
	if (countU > 0)
	{
		charahandle = 9;
	}
	if (countU > 7)
	{
		charahandle = 10;
	}
	if (countU > 15)
	{
		charahandle = 11;
	}
	if (countU > 22)
	{
		charahandle = 10;
	}
	if (countU > 30)
	{
		countU = 0;
	}
	return;
}
VOID CHARA::MOVE_CHARA_CHIP_LEFT()
{
	countL++;
	if (countL > 0)
	{
		charahandle = 3;
	}
	if (countL > 7)
	{
		charahandle = 4;
	}
	if (countL > 15)
	{
		charahandle = 5;
	}
	if (countL > 22)
	{
		charahandle = 4;
	}
	if (countL > 30)
	{
		countL = 0;
	}
	return;
}
VOID CHARA::MOVE_CHARA_CHIP_RIGHT()
{
	countR++;
	if (countR > 0)
	{
		charahandle = 6;
	}
	if (countR > 7)
	{
		charahandle = 7;
	}
	if (countR > 15)
	{
		charahandle = 8;
	}
	if (countR > 22)
	{
		charahandle = 7;
	}
	if (countR > 30)
	{
		countR = 0;
	}
	return;
}