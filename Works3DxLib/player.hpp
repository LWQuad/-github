#pragma once
#include "image.hpp"
class CHARA //キャラクターのクラス
{
public:
	//LOAD_SINGLE_IMAGE image;				//IMAGE構造体
	LOAD_DIV_IMAGE image;
	int speed;					//速さ
	int OldX;					//移動前のX座標
	int OldY;					//移動前のY座標
	int Nowhandle=0;				//現在の画像のハンドル
	RECT coll;					//当たり判定

};

