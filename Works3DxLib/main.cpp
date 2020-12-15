#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include "font.hpp"
#include "map.hpp"
#include "player.hpp"
#include "hitbox.hpp"
#include "battleUI.hpp"
#include "enemystatas.hpp"
#include "playerstatas.hpp"
#include <iostream>
#include <string>
using namespace std;

#define MOVE_MAP_UP 5
#define MOVE_MAP_LEFT 5
#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

enum GAME_SCENE	//ゲームシーンの列挙
{
	GAME_START_SCENE,
	GAME_PLAY_SCENE,
	GAME_BATTLE_SCENE,
	GAME_EVENT_SCENE,
	GAME_END_SCENE
};

class HPbar
{
	int HPwidth = 100;
};

PlayerStates Pstates;

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

VOID MY_BATTLE(VOID);			//バトル画面
VOID MY_BATTLE_PROC(VOID);		//バトル画面の処理
VOID MY_BATTLE_DRAW(VOID);		//バトル画面の描画

VOID MY_EVENT(VOID);			//イベント画面
VOID MY_EVENT_PROC(VOID);		//イベント画面の処理
VOID MY_EVENT_DRAW(VOID);		//イベント画面の描画

LOAD_SINGLE_IMAGE title;
LOAD_SINGLE_IMAGE Bplayer;
LOAD_SINGLE_IMAGE enemy;
LOAD_SINGLE_IMAGE btbk;
LOAD_SINGLE_IMAGE UIback;
LOAD_SINGLE_IMAGE kougekiUI;
LOAD_SINGLE_IMAGE skillUI;
CREATE_FONTHANDLE tanu20;
CREATE_FONTHANDLE tanu30;
MAP_DIV divmap;
MAPINPUT MAPUND;
MAPINPUT MAPMID;
MAPINPUT MAPON;
MAP_HITBOX MAPHIT;
MAP_ENEMY MAPEN;
ENEMY Senemy;
CHARA player;

BATTLE_UI UI;
int GameScene;//ゲームシーンを管理する
int MoveMap = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
/*	SetWindowIconID(IDI_ICON1);*/							//アイコンファイルを読込

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	if (title.LOADING_IMAGE(IMAGE_TITLE) == -1) { return -1; }
	if (Bplayer.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }
	/*if (player.image.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }*/
	if (player.image.LOADING_DIV_IMAGE(IMAGE_PLAYER_INMAP) == -1) { return -1; }
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return -1; }
	if (btbk.LOADING_IMAGE(IMAGE_BATTLE_BACK) == -1) { return -1; }
	if (UIback.LOADING_IMAGE(IMAGE_UI_BACK) == -1) { return -1; }
	if (kougekiUI.LOADING_IMAGE(IMAGE_UI_KOUGEKI) == -1) { return -1; }
	if (skillUI.LOADING_IMAGE(IMAGE_UI_SKILL) == -1) { return -1; }
	SetMouseDispFlag(TRUE);			//マウスカーソルを表示

	GameScene = GAME_PLAY_SCENE;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画
	divmap.DIV_MAP();
	MAPUND.LOADING_MAP(GAME_MAP1_UNDER_TXT);//下のマップ
	MAPUND.MAPSETTING(divmap.width, divmap.height);
	MAPMID.LOADING_MAP(GAME_MAP1_MIDDLE_TXT);//中のマップ
	MAPMID.MAPSETTING(divmap.width, divmap.height);
	MAPON.LOADING_MAP(GAME_MAP1_ON_TXT);//上のマップ
	MAPON.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.LOADING_MAP(GAME_MAP1_HITBOX);//当たり判定のマップ
	MAPHIT.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.SETTING_HITBOX(divmap.width, divmap.height);
	MAPEN.LOADING_MAP(GAME_MAP1_ENEMYMAP);//敵の出現マップ
	MAPEN.MAPSETTING(divmap.width, divmap.height);
	MAPEN.SETTING_HITBOX(divmap.width, divmap.height);

	//start位置の設定
	player.image.x = divmap.width*10; player.image.y =divmap.height*11 ;
	player.Nowhandle = player.image.handle[0];
	/*player.image.IsDraw = TRUE;*/
	//スタートが決まっていなければ
	//if (startPt.x == -1 && startPt.y == -1)
	//{
	//	//エラーメッセージ表示
	//	MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	//}
	Pstates.INPUT_STATES(PLAYER_STATES);
	////ゴールが決まっていなければ
	//if (GoalRect.left == -1)
	//{
	//	//エラーメッセージ表示
	//	MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	//}
	tanu20.CREATE_FONT(20,FONT_TANU_PATH,FONT_TANU_NAME);
	tanu30.CREATE_FONT(30, FONT_TANU_PATH, FONT_TANU_NAME);
	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		//MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得


		//MY_MOUSE_UPDATE();						//マウスの状態を取得

		//MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
			case GAME_START_SCENE:
				MY_START();	//スタート画面
				break;
			case GAME_PLAY_SCENE:
				MY_PLAY();	//プレイ画面
				break;
			case GAME_BATTLE_SCENE:
				MY_BATTLE(); //バトル画面
				break;
			case GAME_EVENT_SCENE:
				MY_EVENT(); //イベント画面
				break;
			case GAME_END_SCENE:
				MY_END(); //エンド画面
				break;
		}
		//DrawGraph(title.x, title.y, title.handle, TRUE);
		//MY_FPS_DRAW();		//FPSの処理[描画]
		


		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		//MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	int DxLib_End();
	return 0;
}
	////フォントハンドルを破棄
	//MY_FONT_DELETE();

	////一時的にインストールしたフォントをアンインストール
	//MY_FONT_UNINSTALL_ONCE();

	////画像ハンドルを破棄
	//MY_DELETE_IMAGE();

	////音楽ハンドルを破棄
	//MY_DELETE_MUSIC();

VOID MY_START()
{
	MY_START_PROC();
	MY_START_DRAW();
	return;
}

VOID MY_START_PROC()
{
	return;
}
VOID MY_START_DRAW()
{
	return;
}

VOID MY_PLAY()
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();
	return;
}

VOID MY_PLAY_PROC()
{
	//プレイヤーの当たり判定を設定
	player.coll.left = player.image.x + 5;
	player.coll.top = player.image.y + 5;
	player.coll.right = player.image.x + player.image.width - 5;
	player.coll.bottom = player.image.y + player.image.height - 5;

	//移動前のプレイヤーの場所を取得
	player.OldX = player.image.x;
	player.OldY = player.image.y;
	if (CheckHitKey(KEY_INPUT_UP) == TRUE)
	{
		player.Nowhandle = player.image.handle[10];
		player.coll.top -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else{ player.image.y -= 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{GameScene = GAME_BATTLE_SCENE;}
		if (MAPON.y[0][0] < 0 && player.image.y < 100)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//マップを描画
					MAPON.y[tate][yoko] += 5;
					MAPMID.y[tate][yoko] += 5;
					MAPUND.y[tate][yoko] += 5;
					MAPHIT.y[tate][yoko] += 5;
					MAPHIT.Hitmap[tate][yoko].bottom += 5;
					MAPHIT.Hitmap[tate][yoko].top += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		/*player.image.x -= 5;*/
		player.Nowhandle = player.image.handle[4];
		player.coll.left -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else {
			player.image.x -= 5;
		}
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.x[0][0] < 0 && player.image.x < 150)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//マップを描画
					MAPON.x[tate][yoko] += 5;
					MAPMID.x[tate][yoko] += 5;
					MAPUND.x[tate][yoko] += 5;
					MAPHIT.x[tate][yoko] += 5;
					MAPHIT.Hitmap[tate][yoko].left += 5;
					MAPHIT.Hitmap[tate][yoko].right += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE)
	{
		player.Nowhandle = player.image.handle[1];
		player.coll.bottom += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else { player.image.y += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.y[MAP_TATE_MAX1 - 1][0] > GAME_HEIGHT && player.image.y > 500)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//マップを描画
					MAPON.y[tate][yoko] -= 5;
					MAPMID.y[tate][yoko] -= 5;
					MAPUND.y[tate][yoko] -= 5;
					MAPHIT.y[tate][yoko] -= 5;
					MAPHIT.Hitmap[tate][yoko].bottom -= 5;
					MAPHIT.Hitmap[tate][yoko].top -= 5;
				}
			}
		}

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		player.Nowhandle = player.image.handle[7];
		player.coll.right += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else { player.image.x += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.x[0][MAP_YOKO_MAX1 - 1] > GAME_WIDTH && player.image.x > 650)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//マップを描画
					MAPON.x[tate][yoko] -= 5;
					MAPMID.x[tate][yoko] -= 5;
					MAPUND.x[tate][yoko] -= 5;
					MAPHIT.x[tate][yoko] -= 5;
					MAPHIT.Hitmap[tate][yoko].left -= 5;
					MAPHIT.Hitmap[tate][yoko].right -= 5;
				}
			}
		}
	}
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x > GAME_WIDTH-divmap.width) { player.image.x = GAME_WIDTH - divmap.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y > GAME_HEIGHT - divmap.height) { player.image.y = GAME_HEIGHT - divmap.height; }
	//player.coll.left = player.image.x + 5;
	//player.coll.top = player.image.y + 5;
	//player.coll.right = player.image.x + player.image.width - 5;
	//player.coll.bottom = player.image.y + player.image.height - 5;
	//if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	//{
	//	player.image.x = player.OldX;
	//	player.image.y = player.OldY;
	//}





	return;
}
VOID MY_PLAY_DRAW()
{
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)//プレイヤーより下のマップ描画
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//マップを描画
			/*if(MAPUND.isVIEW==TRUE)*/
			DrawGraph(
				MAPUND.x[tate][yoko],
				MAPUND.y[tate][yoko],
				divmap.handle[MAPUND.kind[tate][yoko]],
				TRUE);
			/*if (MAPMID.isVIEW == TRUE)*/
			DrawGraph(
				MAPMID.x[tate][yoko],
				MAPMID.y[tate][yoko],
				divmap.handle[MAPMID.kind[tate][yoko]],
				TRUE);
			
			/*if (MAPON.isVIEW == TRUE)*/

		}
	}
	//if (player.image.IsDraw == TRUE)
	//{
		DrawGraph(player.image.x, player.image.y, player.Nowhandle, TRUE);
/*	}*///プレイヤーの描画
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)//プレイヤーより上のマップ描画
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			DrawGraph(
				MAPON.x[tate][yoko],
				MAPON.y[tate][yoko],
				divmap.handle[MAPON.kind[tate][yoko]],
				TRUE);
		}
		//for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		//{
		//	DrawGraph(
		//		MAPHIT.x[tate][yoko],
		//		MAPHIT.y[tate][yoko],
		//		divmap.handle[MAPHIT.kind[tate][yoko]],
		//		TRUE);
		//}
	}
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
{
	for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
	{
		//壁ならば
		if (MAPHIT.kind[tate][yoko] == 63)
		{
			DrawBox(MAPHIT.Hitmap[tate][yoko].left, MAPHIT.Hitmap[tate][yoko].top,
				MAPHIT.Hitmap[tate][yoko].right, MAPHIT.Hitmap[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
		}

	}
}
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
	return;
}

VOID MY_EVENT()
{
	MY_EVENT_PROC();
	MY_EVENT_DRAW();
	return;
}

VOID MY_EVENT_PROC()
{
	return;
}
VOID MY_EVENT_DRAW()
{
	return;
}

VOID MY_BATTLE()
{
	MY_BATTLE_PROC();
	MY_BATTLE_DRAW();
	return;
}

VOID MY_BATTLE_PROC()
{
	UI.CHANGE_COUNT();
	if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)
	{
		UI.count = 0;
		UI.UItag -= 1;
		if (UI.UItag < 0) { UI.UItag = 4; }
	}
	if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)
	{
		UI.count = 0;
		UI.UItag += 1;
		if (UI.UItag > 4) { UI.UItag = 0; }
	}

	if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.UItag == 0)//攻撃選択時
	{

	}
	return;
}

VOID MY_BATTLE_DRAW()
{
	DrawGraph(btbk.x, btbk.y, btbk.handle, TRUE);
	DrawGraph(enemy.x, enemy.y, enemy.handle, TRUE);
	DrawGraph(200, 370, Bplayer.handle, TRUE);
	/*DrawGraph(player.x, player.y, player.handle, TRUE);*/
	/*DrawBox(20, GAME_HEIGHT - 220, 220, GAME_HEIGHT-55, GetColor(255, 255, 0), TRUE);*/
	DrawGraph(20, 330, UIback.handle, TRUE);
	/*DrawStringToHandle(30, 400, "〇攻撃", GetColor(255, 255, 255), tanu30.handle);*/
	DrawGraph(30, 340, kougekiUI.handle, TRUE);
	DrawGraph(30, 380, kougekiUI.handle, TRUE);
	DrawGraph(30, 420, kougekiUI.handle, TRUE);
	DrawGraph(30, 460, kougekiUI.handle, TRUE);
	DrawGraph(30, 500, kougekiUI.handle, TRUE);
	/*DrawStringToHandle(30, 460, "〇防御", GetColor(255, 255, 255), tanu30.handle);
	DrawStringToHandle(30, 490, "〇アイテム", GetColor(255, 255, 255), tanu30.handle);
	DrawStringToHandle(30, 520, "〇にげる", GetColor(255, 255, 255), tanu30.handle);*/
	DrawBox(0, GAME_HEIGHT - 40, GAME_WIDTH, GAME_HEIGHT, GetColor(125, 125, 0), TRUE);
	DrawBox(350-2, 400-2, 350 + 100+2, 420+2, GetColor(255, 255, 255), TRUE);
	float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
	float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;
	DrawBox(350, 400,350+(int)a, 420, GetColor(0, 255, 0), TRUE);
	DrawStringToHandle(320, GAME_HEIGHT-30, "Enter:決定 十字キー:選択 Return:キャンセル", GetColor(255, 255, 255), tanu20.handle);
	DrawFormatStringToHandle(350, 400
		, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.HP, Pstates.HPMAX);
	return;
}

VOID MY_END()
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC()
{
	return;
}
VOID MY_END_DRAW()
{
	return;
}

