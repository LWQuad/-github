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
#define IMAGE_UI_BACK TEXT(".\\IMAGEs\\BattleUI\\UI背景.png")
#define IMAGE_UI_KOUGEKI TEXT(".\\IMAGEs\\BattleUI\\攻撃.png")
#define IMAGE_UI_SKILL TEXT(".\\IMAGEs\\BattleUI\\スキル.png")
#define IMAGE_UI_GUARD TEXT(".\\IMAGEs\\BattleUI\\防御.png")
#define IMAGE_UI_ITEM TEXT(".\\IMAGEs\\BattleUI\\アイテム.png")
#define IMAGE_UI_RUN TEXT(".\\IMAGEs\\BattleUI\\逃げる.png")

#define IMAGE_STATES_CHARA TEXT(".\\IMAGEs\\STATES\\ステータス画面キャラ.png")

#define IMAGE_BATTLE_EFFECT_NORMAL_AT TEXT(".\\IMAGEs\\640×480\\btleffectNormal.png")

class LOAD_SINGLE_IMAGE //画像一枚を読み込むクラス
{
public:
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int UIhandle[5];
	int DhanN = 0;
	vector<int>Divhandle;		//分割画像用のハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw;				//表示の可否

	BOOL LOADING_IMAGE(const char*); //画像を読み込む(画像のパス)
	BOOL LOADING_IMAGE(const char*,int);
};
class LOAD_DIV_IMAGE //分割画像を読み込むクラス
{
public:
	vector<int> Divhandle;	//可変ハンドル
	int x;
	int y;
	int width;
	int height;
	int Divmax = 0;
	//(分割する縦の数、横の数、分割する幅、分割する高さ、画像のパス
	BOOL LOADING_DIV_IMAGE(int,int,int,int,const char*);//分割画像を読み込む
	//（分割する縦の数、分割する横の数、）
};

