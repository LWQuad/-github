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


