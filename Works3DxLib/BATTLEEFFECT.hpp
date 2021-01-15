#pragma once
#include "DxLib.h"
#include "image.hpp"
#include "music.hpp"

class BATTLE_EFFECT//バトルエフェクトを管理するクラス
{
public:
	LOAD_DIV_IMAGE image;
	MUSIC se;
	BOOL isView = FALSE;
	int CountMax = 5;
	int Count = 0;
	int Viewimage = 0;
	int effectflg = 0;
	VOID PLAY_SE();//音を再生する
	VOID MOVE_VIEW_IMAGE();//描画アニメーション
};

enum BATTLE_MESSAGE
{
	ENCOUNT,
	SELECT_NORMAL_AT,
	NORMAL_AT,
	SELECT_SKILL,
	GUARD,
	SELECT_ITEM,
	RUN,
	CRITICAL,
	DEFEAT_EN,
	GET_EXP,
	GIVE_DAMAGE,
	Levelup
};

VOID BATTLE_EFFECT::PLAY_SE()
{
	if (CheckSoundMem(this->se.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, this->se.handle);	//50%の音量にする
		PlaySoundMem(this->se.handle, DX_PLAYTYPE_BACK);
	}
	return;
}

VOID BATTLE_EFFECT::MOVE_VIEW_IMAGE()
{
	if (this->Viewimage < this->image.Divmax)
	{
		WaitTimer(100);
		this->Viewimage++;
	}
	else {
		this->isView = FALSE;
		this->Count = 0;
		this->Viewimage = 0;
		this->effectflg = 1;//次の処理へ移動
	}
	return;
}


