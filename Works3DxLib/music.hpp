#pragma once
#include "windowsystem.h"
#include "DxLib.h"
#define PLAY_SCENE_MUSIC TEXT(".\\MUSIC\\山茶花～サザンカ～.mp3")
#define BATTLE_SCENE_MUSIC1 TEXT(".\\MUSIC\\合戦の時.mp3")
#define BATTLE_SE_NORMALAT TEXT(".\\MUSIC\\SE\\sword.mp3")

#define BATTLE_SE_ENNORMALAT TEXT(".\\MUSIC\\SE\\punch-middle2.mp3")

class MUSIC
{
public:

	char path[PATH_MAX];		//パス
	int handle;

	BOOL LOAD_MUSIC(const char*);//音楽をロードする(音楽のパス)

};