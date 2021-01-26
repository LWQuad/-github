#include "DxLib.h"
#include "map.hpp"

VOID MAPINPUT::RESIZE(int TATE_MAX, int YOKO_MAX)
{
	kind.resize(TATE_MAX, vector<int>(YOKO_MAX));
	width.resize(TATE_MAX, vector<int>(YOKO_MAX));
	height.resize(TATE_MAX, vector<int>(YOKO_MAX));
	x.resize(TATE_MAX, vector<int>(YOKO_MAX));
	y.resize(TATE_MAX, vector<int>(YOKO_MAX));
	mapF.resize(TATE_MAX, vector<int>(YOKO_MAX));
	map.resize(TATE_MAX, vector<int>(YOKO_MAX));
	return;
}

BOOL MAPINPUT::LOADING_MAP(const char* maptxt)//マップデータを読み込む関数(マップファイルパス)
{
	//ifstream ifs(maptxt);
	//string str;
	//int tate = 0, yoko = 0;
	//while (getline(ifs, str, ','))
	//{
	//	this->map[tate][yoko] = atoi(str.c_str());
	//	yoko++;
	//	if (yoko > MAP_YOKO_MAX1 - 1) { yoko = 0; tate++; }
	//}
	//ifs.close();
	ifstream ifs(maptxt);
	string str;
	int tate = 0, yoko = 0;
	while (getline(ifs, str))
	{
		string tmp = "";
		istringstream stream(str);
		while (getline(stream, tmp, ','))
		{
			this->map[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
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



BOOL MAP_DIV::DIV_MAP(const char* path,int div_tate,int div_yoko,int div_scale) {
	
	int div_num = div_tate * div_yoko;
	handle.resize(div_num), kind.resize(div_num);
	int mapRes = LoadDivGraph(
		path,										//マップのパス
		div_num, div_tate, div_yoko,			//マップを分割する数
		div_scale, div_scale,						//画像を分割するの幅と高さ
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
