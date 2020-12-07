#pragma once
#include "windowsystem.h"
#include "map.hpp"
#include <vector>

#define IMAGE_TITLE TEXT(".\\IMAGEs\\Kitune.jpg")
#define IMAGE_PLAYER_BATTLE TEXT(".\\IMAGEs\\playerimage.png")
#define IMAGE_ENEMY1 TEXT(".\\IMAGEs\\enemyimage.png")



class LOAD_SINGLE_IMAGE //画像一枚を読み込むクラス
{
public:
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	vector<int> maphandle;		//マップチップのハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw;				//表示の可否

	BOOL LOADING_IMAGE(const char*); //画像を読み込む(画像のパス)
};

