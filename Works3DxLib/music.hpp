#pragma once
#include "windowsystem.h"
#include "DxLib.h"
class MUSIC
{
public:

	char path[PATH_MAX];		//�p�X
	int handle;

	BOOL LOAD_MUSIC(const char*);//���y�����[�h����(���y�̃p�X)

};