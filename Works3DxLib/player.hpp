#pragma once
#include "image.hpp"
class CHARA //キャラクターのクラス
{
public:
	LOAD_SINGLE_IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y
	int OldX;					//移動前のX座標
	int OldY;					//移動前のY座標
	int OldCenterX;
	int OldCenterY;

	//MUSIC musicShot;			//プレイヤーの発射音

	//BOOL CanShot;				//ショットできるか
	//int ShotReLoadCnt;			//ショットリロード時間
	//int ShotReLoadCntMAX;		//ショットリロード時間(MAX)

	//TAMA tama[TAMA_MAX];		//ショットする弾

	RECT coll;					//当たり判定
	//iPOINT collBeforePt;		//当たる前の座標

};	//キャラクター構造体

