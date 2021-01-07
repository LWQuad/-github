#pragma once
#include "image.hpp"
#include "DxLib.h"

class STATES_UI
{
private:
	int S_countM = 30, C_countM = 30;
public:
	LOAD_SINGLE_IMAGE charaimg, UIimg, back, back2;
	int Ctag = 0;
	int S_count = 0,C_count = 0;
	BOOL CHECK_CHENGE_COUNT_STorPLY();//プレイ画面とステータス画面を行き来する
	//カウントの可否を判定する関数
	BOOL CHECK_CHENGE_COUNT_CATEGORY();//ステータスのカテゴリ変更のタブを管理する
};

BOOL STATES_UI::CHECK_CHENGE_COUNT_STorPLY()
{
	if (S_count >= S_countM)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL STATES_UI::CHECK_CHENGE_COUNT_CATEGORY()
{
	if (C_count >= C_countM)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

