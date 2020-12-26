#pragma once
#include "windowsystem.h"
#include "map.hpp"
#include <vector>
using namespace std;

#define DIV_CHARA_TATE 3
#define DIV_CHARA_YOKO 4
#define DIV_CHARA DIV_CHARA_TATE*DIV_CHARA_YOKO

#define DIV_BT_EFFECT_TATE 5
#define DIV_BT_EFFECT_YOKO 1
#define DIV_BT_EFFECT_WIDTH 240
#define DIV_BT_EFFECT_HEIGHT 240

#define IMAGE_PLAYER_INMAP TEXT(".\\IMAGEs\\charachip.png")

#define IMAGE_TITLE TEXT(".\\IMAGEs\\Kitune.jpg")
#define IMAGE_PLAYER_BATTLE TEXT(".\\IMAGEs\\playerimage.png")
#define IMAGE_ENEMY1 TEXT(".\\IMAGEs\\enemyimage.png")
#define IMAGE_BATTLE_BACK	TEXT(".\\IMAGEs\\battle_back.png")
#define IMAGE_UI_BACK TEXT(".\\IMAGEs\\BattleUI\\UI�w�i.png")
#define IMAGE_UI_KOUGEKI TEXT(".\\IMAGEs\\BattleUI\\�U��.png")
#define IMAGE_UI_SKILL TEXT(".\\IMAGEs\\BattleUI\\�X�L��.png")
#define IMAGE_UI_GUARD TEXT(".\\IMAGEs\\BattleUI\\�h��.png")
#define IMAGE_UI_ITEM TEXT(".\\IMAGEs\\BattleUI\\�A�C�e��.png")
#define IMAGE_UI_RUN TEXT(".\\IMAGEs\\BattleUI\\������.png")

#define IMAGE_STATES_CHARA TEXT(".\\IMAGEs\\STATES\\�X�e�[�^�X��ʃL����.png")

#define IMAGE_BATTLE_EFFECT_NORMAL_AT TEXT(".\\IMAGEs\\640�~480\\btleffectNormal.png")

class LOAD_SINGLE_IMAGE //�摜�ꖇ��ǂݍ��ރN���X
{
public:
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int UIhandle[5];
	int DhanN = 0;
	vector<int>Divhandle;		//�����摜�p�̃n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
	BOOL IsDraw;				//�\���̉�

	BOOL LOADING_IMAGE(const char*); //�摜��ǂݍ���(�摜�̃p�X)
	BOOL LOADING_IMAGE(const char*,int);
};
class LOAD_DIV_IMAGE //�����摜��ǂݍ��ރN���X
{
public:
	vector<int> Divhandle;	//�σn���h��
	int x;
	int y;
	int width;
	int height;
	int Divmax = 0;
	//(��������c�̐��A���̐��A�������镝�A�������鍂���A�摜�̃p�X
	BOOL LOADING_DIV_IMAGE(int,int,int,int,const char*);//�����摜��ǂݍ���
	//�i��������c�̐��A�������鉡�̐��A�j
};

