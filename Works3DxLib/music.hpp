#pragma once
#include "windowsystem.h"
#include "DxLib.h"
class MUSIC
{
public:

	char path[PATH_MAX];		//パス
	int handle;

	BOOL LOAD_MUSIC(const char*);//音楽をロードする(音楽のパス)

};