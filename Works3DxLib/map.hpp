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

//サンプル用
#define GAME_MAP_PATH1 TEXT(".\\IMAGEs\\MAPIMAGE\\mapchip1.png")
#define GAME_MAP1_UNDER_TXT TEXT(".\\MAP\\map1_マップ下.csv")
#define GAME_MAP1_MIDDLE_TXT TEXT(".\\MAP\\map1_マップ中.csv")
#define GAME_MAP1_ON_TXT TEXT(".\\MAP\\map1_マップ上.csv")
#define GAME_MAP1_HITBOX TEXT(".\\MAP\\map1_当たり判定のマップ.csv")
#define GAME_MAP1_ENEMYMAP TEXT(".\\MAP\\map1_敵の出現マップ.csv")

#define MAP_TATE_MAX1		40
#define MAP_YOKO_MAX1		40
#define MAP_SAMP_STx (32*MAP_YOKO_MAX1)-GAME_WIDTH
#define MAP_SAMP_STy (32*MAP_TATE_MAX1)-GAME_HEIGHT

//村用
#define MAP_MURA_PATH TEXT(".\\MAP\\VILLAGE\\村用タイル.png")
#define MAP_MURA_UNDER TEXT(".\\MAP\\VILLAGE\\mura_下.csv")
#define MAP_MURA_MID TEXT(".\\MAP\\VILLAGE\\mura_中.csv")
#define MAP_MURA_ON TEXT(".\\MAP\\VILLAGE\\mura_上.csv")
#define MAP_MURA_ENEMYMAP TEXT(".\\MAP\\VILLAGE\\mura_敵の出現マップ.csv")
#define MAP_MURA_HITBOX TEXT(".\\MAP\\VILLAGE\\mura_当たり判定のマップ.csv")

#define MAP_MURA_TATEMAX	34
#define MAP_MURA_YOKOMAX	103
#define MAP_MURA_STx (32*MAP_MURA_YOKOMAX)-GAME_WIDTH
#define MAP_MURA_STy 0
#define MAP_MURA_DIV_TATE 50
#define MAP_MURA_DIV_YOKO 50

//森用
#define MAP_FOREST_PATH TEXT(".\\MAP\\FOREST\\森用タイル.png")
#define MAP_FOREST_UNDER TEXT(".\\MAP\\FOREST\\forest_下.csv")
#define MAP_FOREST_MID TEXT(".\\MAP\\FOREST\\forest_中.csv")
#define MAP_FOREST_ON TEXT(".\\MAP\\FOREST\\forest_上.csv")
#define MAP_FOREST_ENEMYMAP TEXT(".\\MAP\\FOREST\\forest_敵の出現マップ.csv")
#define MAP_FOREST_HITBOX TEXT(".\\MAP\\FOREST\\forest_当たり判定のマップ.csv")

#define MAP_FOREST_TATEMAX	100
#define MAP_FOREST_YOKOMAX	53
#define MAP_FOREST_STx 0
#define MAP_FOREST_STy (32*MAP_FOREST_TATEMAX)-GAME_HEIGHT
#define MAP_FOREST_DIV_TATE 50
#define MAP_FOREST_DIV_YOKO 50


#define MAP_DIV_WIDTH		32	//画像を分割する幅サイズ
#define MAP_DIV_HEIGHT		32	//画像を分割する高さサイズ
#define MAP_DIV_TATE		32	//画像を縦に分割する数
#define MAP_DIV_YOKO		41	//画像を横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//画像を分割する総数

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
    void MAPSETTING(int,int,int,int,int,int);//マップの座標を初期セットする（マップチップの幅、高さ,初期位置x,y）
	vector<vector<int>> kind, width, height, x,
		y , mapF, map;
	/*-					種類,幅　　高さ　x,y座標　マップの初期化用-*/
};




