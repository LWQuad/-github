#pragma once
#define	GAME_WIDTH 960
#define GAME_HEIGHT 640
#define GAME_COLOR 32
#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"狐火灯篭"	//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

//マウスのボタン
#define MOUSE_BUTTON_CODE	129		//0x0000～0x0080まで

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

enum GAME_SCENE	//ゲームシーンの列挙
{
	GAME_START_SCENE,
	GAME_PLAY_SCENE,
	GAME_BATTLE_SCENE,
	GAME_EVENT_SCENE,
	GAME_END_SCENE,
	GAME_STATES_SCENE,
	GAME_LOAD_MAP_SCENE,
};

