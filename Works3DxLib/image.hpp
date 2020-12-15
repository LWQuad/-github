#pragma once
#include "windowsystem.h"
#include "map.hpp"
#include <vector>

#define DIV_CHARA_TATE 3
#define DIV_CHARA_YOKO 4
#define DIV_CHARA DIV_CHARA_TATE*DIV_CHARA_YOKO

#define IMAGE_PLAYER_INMAP TEXT(".\\IMAGEs\\charachip.png")

#define IMAGE_TITLE TEXT(".\\IMAGEs\\Kitune.jpg")
#define IMAGE_PLAYER_BATTLE TEXT(".\\IMAGEs\\playerimage.png")
#define IMAGE_ENEMY1 TEXT(".\\IMAGEs\\enemyimage.png")
#define IMAGE_BATTLE_BACK	TEXT(".\\IMAGEs\\battle_back.png")
#define IMAGE_UI_BACK TEXT(".\\IMAGEs\\BattleUI\\UI�w�i.png")
#define IMAGE_UI_KOUGEKI TEXT(".\\IMAGEs\\BattleUI\\�U��.png")
#define IMAGE_UI_SKILL TEXT(".\\IMAGEs\\BattleUI\\�X�L��.png")


class LOAD_SINGLE_IMAGE //�摜�ꖇ��ǂݍ��ރN���X
{
public:
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
	BOOL IsDraw;				//�\���̉�

	BOOL LOADING_IMAGE(const char*); //�摜��ǂݍ���(�摜�̃p�X)

};
class LOAD_DIV_IMAGE //�����摜��ǂݍ��ރN���X
{
public:
	int handle[DIV_CHARA];
	int x;
	int y;
	int width;
	int height;

	BOOL LOADING_DIV_IMAGE(const char*);
};

