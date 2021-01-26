#pragma once
#include "windowsystem.h"
#include "DxLib.h"
#define PLAY_SCENE_MUSIC TEXT(".\\MUSIC\\山茶花～サザンカ～.mp3")
#define BATTLE_SCENE_MUSIC1 TEXT(".\\MUSIC\\合戦の時.mp3")
#define END_SCENE_MUSIC_OVER TEXT(".\\MUSIC\\GAME_OVER.mp3")
#define BATTLE_SE_NORMALAT TEXT(".\\MUSIC\\SE\\sword.mp3")
#define TITLE_SCENE_MUSIC TEXT(".\\MUSIC\\春沙雨.mp3")

#define BATTLE_SE_EN_NORMAL_AT TEXT(".\\MUSIC\\SE\\punch-middle2.mp3")
#define BATTLE_SE_CARSOL TEXT(".\\MUSIC\\SE\\カーソル移動1.mp3")
#define BATTLE_SE_ENTER TEXT(".\\MUSIC\\SE\\和太鼓でドン.mp3")
#define BATTLE_SE_HOTAL TEXT(".\\MUSIC\\SE\\火炎魔法1.mp3")

#define BATTLE_SE_SKILL_MUTUKI TEXT(".\\MUSIC\\SE\\火炎魔法1.mp3")
class MUSIC
{
public:

	char path[PATH_MAX];		//パス
	int handle;

	BOOL LOAD_MUSIC(const char*);//音楽をロードする(音楽のパス)
};