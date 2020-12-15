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
#define IMAGE_UI_BACK TEXT(".\\IMAGEs\\BattleUI\\UI背景.png")
#define IMAGE_UI_KOUGEKI TEXT(".\\IMAGEs\\BattleUI\\攻撃.png")
#define IMAGE_UI_SKILL TEXT(".\\IMAGEs\\BattleUI\\スキル.png")


class LOAD_SINGLE_IMAGE //画像一枚を読み込むクラス
{
public:
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw;				//表示の可否

	BOOL LOADING_IMAGE(const char*); //画像を読み込む(画像のパス)

};
class LOAD_DIV_IMAGE //分割画像を読み込むクラス
{
public:
	int handle[DIV_CHARA];
	int x;
	int y;
	int width;
	int height;

	BOOL LOADING_DIV_IMAGE(const char*);
};

