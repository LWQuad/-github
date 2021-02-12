#pragma once
#include "DxLib.h"

class KEYINPUT
{
private:
	char AllKeyState[256];
	char OldKeyState[256];
	BOOL OnlyKeyflg[256] = { TRUE };

public:
	//キーのインプット情報を管理する
	/* 0: 一度入力 */
	int KEYINPUT_ALLACTION(int);
	int KEYINPUT_NORMAL(int);
	int KEYINPUT_UP(int);
};
