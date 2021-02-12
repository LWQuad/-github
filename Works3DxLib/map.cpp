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

BOOL MAPINPUT::LOADING_MAP_TAG(int saveslot,const char* maptagpath)
{
	int ret;
	FILE* fp = fopen(maptagpath, "r");
	while (ret = fscanf(fp, "%d,",
		&MAPtag[saveslot]) != EOF) {};
	return TRUE;
}

BOOL MAPINPUT::LOADING_MAP_COORDINATES(const char* maptxtX,const char* maptxtY)
//マップデータの座標を読み込む関数(X座標のファイルパス、Y座標のファイルパス)
{
	ifstream ifsX(maptxtX),ifsY(maptxtY);
	string strX, strY;
	int tate = 0, yoko = 0;
	while (getline(ifsX, strX))
	{
		string tmp = "";
		istringstream stream(strX);
		while (getline(stream, tmp, ','))
		{
			this->x[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
	}
	tate = 0, yoko = 0;
	while (getline(ifsY, strY))
	{
		string tmp = "";
		istringstream stream(strY);
		while (getline(stream, tmp, ','))
		{
			this->y[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
	}
	ifsX.close(),ifsY.close();
	return TRUE;
}

//マップの座標を保存する関数
BOOL MAPINPUT::SAVE_MAP(int TATE_MAX, int YOKO_MAX,const char* mapdatapathX,const char* mapdatapathY,
	const char* maptagpath)
{
	ofstream ofsX(mapdatapathX), ofsY(mapdatapathY), ofsTag(maptagpath);
	if (!ofsX||!ofsY)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), ERROR_MESSAGE, "ファイルの読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			ofsX << this->x[tate][yoko]<<",";
			ofsY << this->y[tate][yoko]<<",";
		}
		ofsX << endl;
		ofsY << endl;
	}
	if (TATE_MAX == MAP_FOREST_TATEMAX && YOKO_MAX == MAP_FOREST_YOKOMAX) {
		ofsTag << 1 << endl;
	}
	return TRUE;
}

//マップデータの座標を設定する関数(マップチップの幅、マップチップの高さ)
VOID MAPINPUT::MAPSETTING(int chipwidth, int chipheight,int Stx,int Sty,int TATE_MAX,int YOKO_MAX)
{
	

	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
			this->x[tate][yoko] -= Stx;
			this->y[tate][yoko] -= Sty;
			this->isVIEW = FALSE;
		}
	}
	return;
}

VOID MAPINPUT::INTARACTIV_MAP(int TATE_MAX, int YOKO_MAX)
{
	mapmove++;
	if (mapmove==10)
	{
		for (int tate = 0; tate < TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < YOKO_MAX; yoko++)
			{
				//マップを描画
				if (kind[tate][yoko] == 1460)
				{
					kind[tate][yoko] = 1461;
				}
			}
		}
	}
	if (mapmove==20)
	{
		for (int tate = 0; tate < TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < YOKO_MAX; yoko++)
			{
				//マップを描画
				if (kind[tate][yoko] == 1461)
				{
					kind[tate][yoko] = 1460;
				}
			}
		}
		mapmove = 0;
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
		MessageBox(GetMainWindowHandle(), ERROR_MESSAGE, "マップ画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;

}
