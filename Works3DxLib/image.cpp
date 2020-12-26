#include "DxLib.h"
#include "image.hpp"
#include "windowsystem.h"
#include "map.hpp"

BOOL LOAD_SINGLE_IMAGE::LOADING_IMAGE(const char* pathname)
{
	strcpy(this->path, pathname);
	this->handle = LoadGraph(this->path);			//読み込み
	if (this->handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), pathname, "画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	GetGraphSize(this->handle, &this->width, &this->height);	//画像の幅と高さを取得
	this->x = GAME_WIDTH / 2 - this->width / 2;		//左右中央揃え
	this->y = GAME_HEIGHT / 2 - this->height / 2;		//上下中央揃え
	return TRUE;
}

BOOL LOAD_SINGLE_IMAGE::LOADING_IMAGE(const char* pathname,int handleNum)
{
	strcpy(this->path, pathname);
	this->UIhandle[handleNum] = LoadGraph(this->path);			//読み込み
	if (this->UIhandle[handleNum] == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), pathname, "画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	GetGraphSize(this->UIhandle[handleNum], &this->width, &this->height);	//画像の幅と高さを取得
	handle = LoadGraph(this->path);
	GetGraphSize(UIhandle[handleNum], &this->width, &this->height);
	this->x = GAME_WIDTH / 2 - this->width / 2;		//左右中央揃え
	this->y = GAME_HEIGHT / 2 - this->height / 2;		//上下中央揃え
	return TRUE;
}

BOOL LOAD_DIV_IMAGE::LOADING_DIV_IMAGE(int divtate,int divyoko,int divwidth,int divheight,
const char* divimagepath)
{
	int divmax = divtate * divyoko;
	this->Divmax = divmax - 1;
	this->Divhandle.resize(divmax);//分割数に合わせてハンドル数を増やす
	int mapRes = LoadDivGraph(
		divimagepath,										//マップのパス
		divmax, divtate, divyoko,			//マップを分割する数
		divwidth, divheight,						//画像を分割する幅と高さ
		&this->Divhandle[0]);								//分割した画像が入るハンドル
	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "キャラ画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(this->Divhandle[0], &this->width, &this->height);
	return TRUE;
}

