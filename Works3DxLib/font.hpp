#pragma once
#include <iostream>
#include "DxLib.h"
#include "windowsystem.h"
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")			//フォントの名前
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

class CREATE_FONTHANDLE
{
public:
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ

	BOOL CREATE_FONT(int, const char*, const char*);
	BOOL CREATE_FONT_NONEDGE(int, const char*, const char*);
	//フォントハンドルの作成
	//(フォントサイズ　フォントのパス　フォントの名前)

	~CREATE_FONTHANDLE()//フォントハンドルを削除
	{
		DeleteFontToHandle(this->handle);
	}
};
