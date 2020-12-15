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

BOOL LOAD_DIV_IMAGE::LOADING_DIV_IMAGE(const char* divimagepath)
{
	int mapRes = LoadDivGraph(
		divimagepath,										//マップのパス
		DIV_CHARA, DIV_CHARA_TATE, DIV_CHARA_YOKO,			//マップを分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&this->handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "キャラ画像の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;
}

