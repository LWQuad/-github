#pragma once
#include "image.hpp"
#include "DxLib.h"
class START_UI
{
private:
	int E_countM = 30, C_countM = 30;
public:
	int tag = 0;
	int E_count = 0, C_count = 0;
	int NewgameS, LoadgameS;
	BOOL CHECK_CHENGE_COUNT_ENTER();//�G���^�[�������֐�
	BOOL CHECK_CHENGE_COUNT_CATEGORY();//�X�e�[�^�X�̃J�e�S���ύX�̃^�u���Ǘ�����

};

BOOL START_UI::CHECK_CHENGE_COUNT_ENTER()
{
	if (E_count >= E_countM)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL START_UI::CHECK_CHENGE_COUNT_CATEGORY()
{
	if (C_count >= C_countM)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

