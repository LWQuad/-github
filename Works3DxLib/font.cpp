#include "font.hpp"

BOOL CREATE_FONTHANDLE::CREATE_FONT(int fontsize,const char* fontpath,const char* fontname)
	{
	strcpy_s(this->path, sizeof(this->path), fontpath);	//パスをコピー
	strcpy_s(this->name, sizeof(this->name), fontname);	//フォント名をコピー
	this->handle = -1;								//ハンドルを初期化
	this->size = fontsize;								//サイズを引数にする
	this->bold = 1;								//太さ1
	this->type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	this->handle = CreateFontToHandle(this->name, this->size, this->bold, this->type);
	//フォントハンドル作成できないとき、エラー
	if (this->handle == -1) { MessageBox(GetMainWindowHandle(), fontpath, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }
	return TRUE;
	}
