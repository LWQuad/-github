#pragma once
#include "windowsystem.h"
#include "DxLib.h"

class CHANGE_TIME {
private:
	int SunColor = GetColor(255, 135, 0);
	int NightColor = GetColor(34, 39, 45);
	int FullTime = 30;
	int FPS = 60.0; int OneminutesSecond = 60.0;
public:
	int i = 0;
	double FirstTime = 0.0;
	BOOL GetFTimeflg = TRUE;
	float R = 255, G = 135, B = 0;
	float nR = 34, nG = 39, nB = 45;
	float BufAlpha = 0, BufAlphaDark = 0;
	float Time = 0;
	int Alpha = 0, DarkAlpha = 0;
	VOID ChangingLight();
	BOOL Nightflg = FALSE;
	BOOL Sunflg = TRUE;
	int NowColor;
	int NowHours=0;
};

VOID CHANGE_TIME::ChangingLight()
{
	//ŠÖ”‹N“®Žžˆê“x‚¾‚¯Œ»ÝŽž‚ðŽæ“¾
	if (GetFTimeflg == TRUE) {
		FirstTime = GetNowCount();
		GetFTimeflg = FALSE;
	}

	if (float buf = (GetNowCount() - FirstTime) / 1000.0 / 10 > i)
	{
		NowHours=i;
		i++;
	}
	//PM0:00‚©‚ç
	switch (NowHours)
	{
	case 0:
		return;
		break;
	case 1:
		return;
		break;
	case 2:
		return;
		break;
	case 3:
		return;
		break;
	case 4:
		BufAlpha += 124.0 / FPS/40;
		Alpha = int(BufAlpha);
		return;
		break;
	case 5:
		BufAlpha += 124.0 / FPS / 40;
		Alpha = int(BufAlpha);
		return;
		break;
	case 6:
		BufAlpha -= 124.0 / FPS / 60;
		Alpha = int(BufAlpha);
		BufAlphaDark += 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 7:
		BufAlpha -= 124.0 / FPS / 60;
		Alpha = int(BufAlpha);
		BufAlphaDark += 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 8:
		BufAlpha -= 124.0 / FPS / 60;
		Alpha = int(BufAlpha);
		BufAlphaDark += 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 9:
		BufAlphaDark += 124.0 / FPS / 40;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 10:
		return;
		break;
	case 11:
		return;
		break;
	case 12:
		return;
		break;
	case 13:
		return;
		break;
	case 14:
		return;
		break;
	case 15:
		return;
		break;
	case 16:
		BufAlphaDark -= 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 17:
		BufAlpha += 124.0 / FPS / 40;
		Alpha = int(BufAlpha);
		BufAlphaDark -= 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 18:
		BufAlpha += 124.0 / FPS / 40;
		Alpha = int(BufAlpha);
		BufAlphaDark -= 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 19:
		BufAlpha -= 124.0 / FPS / 20;
		Alpha = int(BufAlpha);
		BufAlphaDark -= 124.0 / FPS / 20;
		DarkAlpha = int(BufAlphaDark);
		return;
		break;
	case 20:
		return;
		break;
	case 21:
		return;
		break;
	case 22:
		return;
		break;
	case 23:
		return;
		break;
	case 24:
		GetFTimeflg = TRUE;
		BufAlpha = 0, BufAlphaDark = 0;
		Alpha = 0, DarkAlpha = 0;
		i = 0;
		return;
		break;
	}
}


