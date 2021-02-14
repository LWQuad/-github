#pragma once
#include "DxLib.h"
#include "image.hpp"
#include "music.hpp"

class BATTLE_EFFECT//�o�g���G�t�F�N�g���Ǘ�����N���X
{
public:
	LOAD_DIV_IMAGE image;
	MUSIC se;
	char sepath[MAX_PATH];
	char imgpath[MAX_PATH];
	BOOL isView = FALSE;
	int CountMax = 5;
	int Count = 0;
	int Viewimage = 0;
	int effectflg = 0;
	VOID PLAY_SE();//�����Đ�����
	VOID MOVE_VIEW_IMAGE();//�`��A�j���[�V����
	VOID LOADING_PATH(int);
};

enum BATTLE_MESSAGE
{
	ENCOUNT,
	SELECT_NORMAL_AT,
	NORMAL_AT,
	SELECT_SKILL,
	GUARD,
	SELECT_ITEM,
	RUN,
	CRITICAL,
	DEFEAT_EN,
	GET_EXP,
	GIVE_DAMAGE,
	Levelup,
	NOT_ENOUGH_MP,
	SKILL_IAI_WAZANAME,
	SKILL_KIKON_WAZANAME,
	SKILL_KEN_WAZANAME,
	SKILL_MAGIC_WAZANAME,
	SKILL_IAI_WAZA_AT,
	SKILL_KIKON_WAZA_AT,
	SKILL_KEN_WAZA_AT,
	SKILL_MAGIC_WAZA_AT,
	ITEM_VIEW_NAME,
	ITEM_WITCH_USE,
	ITEM_USE_MES,
	ITEM_KOUKA_MES,
	ITEM_NOT_USE,
	ENEMY_ATTACK_NORMAL
};

VOID BATTLE_EFFECT::PLAY_SE()
{
	if (CheckSoundMem(this->se.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, this->se.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(this->se.handle, DX_PLAYTYPE_BACK);
	}
	return;
}

VOID BATTLE_EFFECT::MOVE_VIEW_IMAGE()
{
	if (this->Viewimage < this->image.Divmax)
	{
		WaitTimer(100);
		this->Viewimage++;
	}
	else {
		this->isView = FALSE;
		this->Count = 0;
		this->Viewimage = 0;
		this->effectflg = 1;//���̏����ֈړ�
	}
	return;
}

VOID BATTLE_EFFECT::LOADING_PATH(int skillNum)
{
	switch (skillNum)
	{
	case 0:
		strcpy(this->sepath, BATTLE_SE_SKILL_MUTUKI);
		strcpy(this->imgpath, IMAGE_BE_SKILL_IAI_MUTUKI);
		break;
	}
	return;
}
