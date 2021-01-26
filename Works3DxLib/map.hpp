#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "windowsystem.h"
#include "DxLib.h"
#include <string>
using namespace std;

#define GAME_MAP_PATH1 TEXT(".\\IMAGEs\\MAPIMAGE\\mapchip1.png")
#define GAME_MAP1_UNDER_TXT TEXT(".\\MAP\\map1_マップ下.csv")
#define GAME_MAP1_MIDDLE_TXT TEXT(".\\MAP\\map1_マップ中.csv")
#define GAME_MAP1_ON_TXT TEXT(".\\MAP\\map1_マップ上.csv")
#define GAME_MAP1_HITBOX TEXT(".\\MAP\\map1_当たり判定のマップ.csv")
#define GAME_MAP1_ENEMYMAP TEXT(".\\MAP\\map1_敵の出現マップ.csv")

#define MAP_MURA_UNDER_TXT TEXT("")


#define MAP_DIV_WIDTH		32	//画像を分割する幅サイズ
#define MAP_DIV_HEIGHT		32	//画像を分割する高さサイズ
#define MAP_DIV_TATE		32	//画像を縦に分割する数
#define MAP_DIV_YOKO		41	//画像を横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//画像を分割する総数
#define MAP_TATE_MAX1		40
#define MAP_YOKO_MAX1		40
using namespace std;

class MAP_DIV//マップチップ画像を管理する関数
{
public:
	vector<int> handle,kind;
	int width;							//幅
	int height;							//高

	BOOL DIV_MAP(const char*,int,int,int);
};

class MAPINPUT //マップを読み込むクラス
{
public:
	BOOL LOADING_MAP(const char*);//マップを読み込む（マップのパス）
	BOOL isVIEW;//表示できるかを示す
	VOID RESIZE(int, int);
    void MAPSETTING(int,int);//マップの座標を初期セットする（マップチップの幅、高さ）
	vector<vector<int>> kind,width,height,x,y,mapF,map;
	/*-					種類,幅　　高さ　x,y座標　マップの初期化用-*/
};




