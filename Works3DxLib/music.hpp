#pragma once
#include "windowsystem.h"
#include "DxLib.h"
#define PLAY_SCENE_MUSIC TEXT(".\\MUSIC\\�R���ԁ`�T�U���J�`.mp3")
#define BATTLE_SCENE_MUSIC1 TEXT(".\\MUSIC\\����̎�.mp3")
#define BATTLE_SE_NORMALAT TEXT(".\\MUSIC\\SE\\sword.mp3")

#define BATTLE_SE_ENNORMALAT TEXT(".\\MUSIC\\SE\\punch-middle2.mp3")

class MUSIC
{
public:

	char path[PATH_MAX];		//�p�X
	int handle;

	BOOL LOAD_MUSIC(const char*);//���y�����[�h����(���y�̃p�X)

};