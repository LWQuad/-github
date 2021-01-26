#include "DxLib.h"
#include "map.hpp"

VOID MAPINPUT::RESIZE(int TATE_MAX, int YOKO_MAX)
{
	kind.resize(TATE_MAX, vector<int>(YOKO_MAX));
	return;
}

BOOL MAPINPUT::LOADING_MAP(const char* maptxt)//マップデータを読み込む関数(マップファイルパス)
{
	ifstream ifs(maptxt);
	string str;
	int tate = 0, yoko = 0;
	while (getline(ifs, str, ','))
	{
		this->map[tate][yoko] = atoi(str.c_str());
		yoko++;
		if (yoko > MAP_YOKO_MAX1 - 1) { yoko = 0; tate++; }
	}
	ifs.close();
	return TRUE;
}

VOID MAPINPUT::MAPSETTING(int chipwidth, int chipheight)
//マップデータの座標を設定する関数(マップチップの幅、マップチップの高さ)
{
	

	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			this->mapF[tate][yoko] = this->map[tate][yoko];

			//マップの種類をコピー
			this->kind[tate][yoko] = this->map[tate][yoko];

			//マップの幅と高さをコピー
			this->width[tate][yoko] = chipwidth;
			this->height[tate][yoko] = chipheight;

			//マップの座標を設定
			this->x[tate][yoko] =(yoko * this->width[tate][yoko]);
			this->y[tate][yoko] =(tate * this->height[tate][yoko]);
			this->x[tate][yoko] -= 10 * chipwidth;
			this->y[tate][yoko] -= 20 * chipheight;
			this->isVIEW = FALSE;
		}
	}
	return;
}



BOOL MAP_DIV::DIV_MAP() {
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH1,										//マップのパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//マップを分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&this->handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "マップ画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;

}
