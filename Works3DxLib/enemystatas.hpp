#pragma once
#include <iostream>
#include "DxLib.h"
#include "playerstatus.hpp"
#include "image.hpp"

#define ES_GLASS_OKAUMIUSHI TEXT(".\\STATES\\ENEMYSTATUS\\OKAUMIUSHI.csv")
#define ES_GLASS_SURIMEUNKOU TEXT(".\\STATES\\ENEMYSTATUS\\SURIMEUNKOU.csv")
#define ES_GLASS_GOLDUMIUSHI TEXT(".\\STATES\\ENEMYSTATUS\\GOLDUMIUSHI.csv")
#define ES_GLASS_GREYLOTUS TEXT(".\\STATES\\ENEMYSTATUS\\GREYLOTUS.csv")
#define ES_GLASS_YAKINKOROGI TEXT(".\\STATES\\ENEMYSTATUS\\YAKINKOROGI.csv")
#define ES_GLASS_KYORYOBATTA TEXT(".\\STATES\\ENEMYSTATUS\\KYORYOBATTA.csv")

class EnemyStates :public PlayerStates
{
public:
	LOAD_SINGLE_IMAGE image, battleback;
	VOID ENEMY_KIND_FLAG(int);//�G�������_���ɑI��Ńf�[�^��ǂݍ��ފ֐�
	VOID ENEMY_BOSS_FLAG();
};

VOID EnemyStates::ENEMY_BOSS_FLAG()
{
	INPUT_STATES(ES_GLASS_GREYLOTUS);
	image.LOADING_IMAGE(IMAGE_ENEMY_GREYLOTUS);
	if (battleback.LOADING_IMAGE(IMAGE_BATTLE_BACK_NUMA) == FALSE);
	
}

VOID EnemyStates::ENEMY_KIND_FLAG(int Time)
{
	if (Time < 6 || Time>20)
	{
		if (battleback.LOADING_IMAGE(IMAGE_BATTLE_BACK) == FALSE);
		int kindflag = GetRand(100);
		if (kindflag > 80)
		{
			//�S�[���h�E�~�E�V
			INPUT_STATES(ES_GLASS_GOLDUMIUSHI);
			image.LOADING_IMAGE(IMAGE_ENEMY_GOLDUMIUSHI);
			return;
		}
		else if (kindflag > 30)
		{
			//�I�J�E�~�E�V�@40%
			INPUT_STATES(ES_GLASS_OKAUMIUSHI);
			image.LOADING_IMAGE(IMAGE_ENEMY_OKAUMIUSHI);
			return;
		}
		else
		{
			//�X���C���A���R�E�@30%
			INPUT_STATES(ES_GLASS_SURIMEUNKOU);
			image.LOADING_IMAGE(IMAGE_ENEMY_SURIMEUNKOU);
			return;
		}
	}
	else
	{
		if (battleback.LOADING_IMAGE(IMAGE_BATTLE_BACK_NIGHT) == FALSE);
		int kindNflag = GetRand(100);
		if (kindNflag > 50)
		{
			//�L���E�����E�o�b�^
			INPUT_STATES(ES_GLASS_KYORYOBATTA);
			image.LOADING_IMAGE(IMAGE_ENEMY_KYORYOBATTA);
			return;
		}
		else
		{
			//���L���R�I���M
			INPUT_STATES(ES_GLASS_YAKINKOROGI);
			image.LOADING_IMAGE(IMAGE_ENEMY_YAKINKOROGI);
			return;
		}
	}
}

