#pragma once
#include "image.hpp"

class STATES_UI
{
public:
	LOAD_SINGLE_IMAGE charaimage;//ステータス画面で表示するキャラの画像
	int Scount=0;//プレイシーンとステータスシーンを入れ替えるときに使うカウント
	int ScountMax = 30;//↑の切り替えるタイミング

};