#pragma once
#include "DxLib.h"
#include "image.hpp"
class BATTLE_EFFECT//バトルエフェクトを管理するクラス
{
public:
	LOAD_DIV_IMAGE image;
	BOOL isView = FALSE;
	int CountMax = 5;
	int Count = 0;
	int Viewimage = 0;
};
