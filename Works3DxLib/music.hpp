#pragma once
#include "windowsystem.h"
#include "DxLib.h"
#define PLAY_SCENE_MUSIC TEXT(".\\MUSIC\\�R���ԁ`�T�U���J�`.mp3")
#define BATTLE_SCENE_MUSIC1 TEXT(".\\MUSIC\\����̎�.mp3")
#define END_SCENE_MUSIC_OVER TEXT(".\\MUSIC\\GAME_OVER.mp3")
#define BATTLE_SE_NORMALAT TEXT(".\\MUSIC\\SE\\sword.mp3")
#define TITLE_SCENE_MUSIC TEXT(".\\MUSIC\\�t���J.mp3")

#define BATTLE_SE_EN_NORMAL_AT TEXT(".\\MUSIC\\SE\\punch-middle2.mp3")
#define BATTLE_SE_CARSOL TEXT(".\\MUSIC\\SE\\�J�[�\���ړ�1.mp3")
#define BATTLE_SE_ENTER TEXT(".\\MUSIC\\SE\\�a���ۂŃh��.mp3")
#define BATTLE_SE_HOTAL TEXT(".\\MUSIC\\SE\\�Ή����@1.mp3")

#define BATTLE_SE_SKILL_MUTUKI TEXT(".\\MUSIC\\SE\\�Ή����@1.mp3")
class MUSIC
{
public:

	char path[PATH_MAX];		//�p�X
	int handle;

	BOOL LOAD_MUSIC(const char*);//���y�����[�h����(���y�̃p�X)
};