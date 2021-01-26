#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "windowsystem.h"
#include "DxLib.h"
#include <string>
using namespace std;

#define GAME_MAP_PATH1 TEXT(".\\IMAGEs\\MAPIMAGE\\mapchip1.png")
#define GAME_MAP1_UNDER_TXT TEXT(".\\MAP\\map1_マップ下.txt")
#define GAME_MAP1_MIDDLE_TXT TEXT(".\\MAP\\map1_マップ中.txt")
#define GAME_MAP1_ON_TXT TEXT(".\\MAP\\map1_マップ上.txt")
#define GAME_MAP1_HITBOX TEXT(".\\MAP\\map1_当たり判定のマップ.txt")
#define GAME_MAP1_ENEMYMAP TEXT(".\\MAP\\map1_敵の出現マップ.txt")

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
	int handle[MAP_DIV_NUM];			//分割した画像ハンドルを取得
	int kind[MAP_DIV_NUM];				//マップの種類
	int width;							//幅
	int height;							//高

	BOOL DIV_MAP();
};

class MAPINPUT //マップを読み込むクラス
{
public:
	int kind[MAP_TATE_MAX1][MAP_YOKO_MAX1];				//マップの種類
	int width[MAP_TATE_MAX1][MAP_YOKO_MAX1];							//幅
	int height[MAP_TATE_MAX1][MAP_YOKO_MAX1];							//高
	int x[MAP_TATE_MAX1][MAP_YOKO_MAX1];
	int y[MAP_TATE_MAX1][MAP_YOKO_MAX1];
	int mapF[MAP_TATE_MAX1][MAP_YOKO_MAX1];//マップデータを格納する二次元配列
	int map[MAP_TATE_MAX1][MAP_YOKO_MAX1];//マップデータを格納する二次元配列
	BOOL LOADING_MAP(const char*);//マップを読み込む（マップのパス）
	BOOL isVIEW;//表示できるかを示す
	VOID RESIZE(int, int);
    void MAPSETTING(int,int);//マップの座標を初期セットする（マップチップの幅、高さ）

	vector<vector<int>> kind;

};




