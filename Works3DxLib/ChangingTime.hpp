#pragma once
#include "windowsystem.h"
#include "DxLib.h"

class CHANGE_TIME {
private:
	int SunColor = GetColor(255, 135, 0);
	int NightColor = GetColor(68, 78, 90);
	int FullTime = 30;
	int FPS = 60.0; int OneminutesSecond = 60.0;
public:
	int i = 0;
	double FirstTime = 0.0;
	BOOL GetFTimeflg = TRUE;
	float R, G, B = 0.0;
	float BufAlpha = 0;
	float Time = 0;
	int Alpha = 0;
	VOID ChangingLight();
	BOOL Nightflg = FALSE;
	BOOL Sunflg = TRUE;
	int NowColor;
	int NowHours=0;
	//CHANGE_TIME()
	//{
	//	60*60*24
	//}

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
		R = 255, G = 135, B = 0;
		BufAlpha += 124.0 / FPS/40;
		Alpha = int(BufAlpha);
		return;
		break;
	case 5:
		R = 255, G = 135, B = 0;
		BufAlpha += 124.0 / FPS / 40;
		Alpha = int(BufAlpha);
		return;
		break;
	case 6:
		R -= (255 - 68) / FPS / 40.0;
		G -= (255 - 78) / FPS / 40;
		B += 90 / FPS / 40;
		return;
		break;
	case 7:
		R -= (255 - 68) / FPS / 40.0;
		G -= (255 - 78) / FPS / 40;
		B += 90 / FPS / 40;
		return;
		break;
	case 8:
		R -= (255 - 68) / FPS / 40;
		G -= (255 - 78) / FPS / 40;
		B += 90 / FPS / 40;
		return;
		break;
	case 9:
		R -= (255 - 68) / FPS / 40;
		G -= (255 - 78) / FPS / 40;
		B += 90 / FPS / 40;
		return;
		break;
	case 10:
		R -= (255 - 68) / FPS / 40;
		G -= (255 - 78) / FPS / 40;
		B += 90 / FPS / 40;
		return;
		break;
	}
}


