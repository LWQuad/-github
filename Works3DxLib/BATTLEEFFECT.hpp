#pragma once
#include "DxLib.h"
#include "image.hpp"
class BATTLE_EFFECT//�o�g���G�t�F�N�g���Ǘ�����N���X
{
public:
	LOAD_DIV_IMAGE image;
	BOOL isView = FALSE;
	int CountMax = 5;
	int Count = 0;
	int Viewimage = 0;
};
