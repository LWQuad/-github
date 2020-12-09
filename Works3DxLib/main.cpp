#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include "font.hpp"
#include "map.hpp"
#include "player.hpp"
#include "hitbox.hpp"
#include <iostream>
#include <string>
using namespace std;

#define PLAYER_STATES TEXT(".\\STATES\\PlayerStates.csv")

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



class PlayerStates
{
private:
	int fHP = 25;
	int fMP = 20;
	int fSTR = 16;
	int fAT = 0;
	int fAVI = 25;
	int fLv = 1;
	int fEXP = 0;

	//statesUpの基礎値
	int uHP = 8;
	int uMP = 2;
	int uSTR = 5;
	int uAVI = 6;
public:
	int HP,MP,STR,AT,AVG,Lv,EXP;
	int EXPMAX;
	void INPUT_STATES()//ファイルからステータスのロード
	{
		int ret;
		FILE* fp = fopen(PLAYER_STATES, "r");
		while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,", &HP, &MP, &STR, &Lv, &EXP, &EXPMAX) != EOF) {};
		fclose(fp);
		return;
	}

	void SAVE_STATES()//ステータスのセーブ
	{
		FILE* fp = fopen(PLAYER_STATES, "w");
		fprintf(fp, "%d,%d,%d,%d,%d,%d,", HP, MP, STR, Lv, EXP, EXPMAX);
		fclose(fp);
		return;
	}

	void LEVELUP()//レベルアップ関数（途中）
	{
		SRand(1);
		int randam = Lv / 10+2;
		HP += uHP*Lv/10+GetRand(randam);
		return;
	}
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
CREATE_FONTHANDLE tanu20;
MAP_DIV divmap;
MAPINPUT MAPUND;
MAPINPUT MAPMID;
MAPINPUT MAPON;
MAP_HITBOX MAPHIT;
CHARA player;
int GameScene;//ゲームシーンを管理する

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
	if (player.image.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return -1; }
	SetMouseDispFlag(TRUE);			//マウスカーソルを表示

	GameScene = GAME_PLAY_SCENE;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画
	divmap.DIV_MAP();
	MAPUND.LOADING_MAP(GAME_MAP1_UNDER_TXT);
	MAPUND.MAPSETTING(divmap.width, divmap.height);
	MAPMID.LOADING_MAP(GAME_MAP1_MIDDLE_TXT);
	MAPMID.MAPSETTING(divmap.width, divmap.height);
	MAPON.LOADING_MAP(GAME_MAP1_ON_TXT);
	MAPON.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.LOADING_MAP(GAME_MAP1_HITBOX);
	MAPHIT.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.SETTING_HITBOX(divmap.width, divmap.height);

	//start位置の設定
	player.image.x = divmap.width*10; player.image.y =divmap.height*11 ;
	player.image.IsDraw = TRUE;
	//スタートが決まっていなければ
	//if (startPt.x == -1 && startPt.y == -1)
	//{
	//	//エラーメッセージ表示
	//	MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	//}

	////ゴールが決まっていなければ
	//if (GoalRect.left == -1)
	//{
	//	//エラーメッセージ表示
	//	MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	//}
	tanu20.CREATE_FONT(20,FONT_TANU_PATH,FONT_TANU_NAME);
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
		Pstates.INPUT_STATES();
		Pstates.SAVE_STATES();

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
		if (MAPON.y[0][0] < 0 && player.image.y<100)
		{
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
		else { player.image.y -= 5; }
		/*player.CenterY -= 5;*/
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		if (MAPON.x[0][0] < 0 && player.image.x<150)
		{
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
		else { player.image.x -= 5; }
		/*player.CenterX -= 5;*/
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE)
	{
		if (MAPON.y[MAP_TATE_MAX1 - 1][0] > GAME_HEIGHT && player.image.y > 500)
		{
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
		else{player.image.y += 5;}
		/*player.CenterY += 5;*/
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		if (MAPON.x[0][MAP_YOKO_MAX1 - 1] > GAME_WIDTH&&player.image.x>650)
		{
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
		else { player.image.x += 5; }
	}
	player.coll.left = player.image.x + 5;
	player.coll.top = player.image.y + 5;
	player.coll.right = player.image.x + player.image.width - 5;
	player.coll.bottom = player.image.y + player.image.height - 5;
	if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		player.image.x = player.OldX;
		player.image.y = player.OldY;
	}
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
	if (player.image.IsDraw == TRUE)
	{
		DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	}//プレイヤーの描画
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
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			DrawGraph(
				MAPHIT.x[tate][yoko],
				MAPHIT.y[tate][yoko],
				divmap.handle[MAPHIT.kind[tate][yoko]],
				TRUE);
		}
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

		////通路ならば
		//if (mapData[tate][yoko] == t)
		//{
		//	DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
		//}
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
	return;
}

VOID MY_BATTLE_DRAW()
{
	DrawGraph(enemy.x, enemy.y, enemy.handle, TRUE);
	/*DrawGraph(player.x, player.y, player.handle, TRUE);*/
	DrawStringToHandle(0, 0, "HP", GetColor(255, 255, 255), tanu20.handle);
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

