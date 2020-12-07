#include "music.hpp"

BOOL MUSIC::LOAD_MUSIC(const char* musicpath)
	{
	strcpy_s(path, musicpath);				//パスの設定
	handle = LoadSoundMem(path);			//読み込み
	if (handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), musicpath, "音楽の読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	return TRUE;
	}
