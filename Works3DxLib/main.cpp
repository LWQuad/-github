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
#include "BATTLEEFFECT.hpp"
#include "Item.hpp"
#include "music.hpp"
#include "StatesUI.hpp"
#include "startUI.hpp"
#include "event.hpp"
#include <iostream>
#include <string>
#include <vector>

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
	GAME_END_SCENE,
	GAME_STATES_SCENE
};



class HPbar
{
	int HPwidth = 100;
};

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

VOID MY_STATES(VOID);			//イベント画面
VOID MY_STATES_PROC(VOID);		//イベント画面の処理
VOID MY_STATES_DRAW(VOID);		//イベント画面の描画

VOID BATTLE_PROC_NEW(VOID);		//バトルシーンを初期化する関数
BOOL LOADING_FULL_IMAGE(VOID);	//画像全てをロードする関数
VOID LOADING_FULL_MAP(VOID);	//マップを読み込む関数
VOID CREATE_FULL_FONT(VOID);	//フォントを作成する関数
BOOL LOADING_FULL_MUSIC(VOID);	//音楽を読み込む関数
BOOL LOADING_SKILL_IMGandSE(int,int); //スキル使用時にSEと画像を読み込む
VOID INPUTBTLSTATES_BUF(VOID);	//1戦闘用にステータスを退避させる関数
VOID PLAY_CARSOL_SOUND(VOID);	//カーソル音を鳴らす(時間短縮用)
VOID PLAY_ENTER_SOUND(int);	//決定音を鳴らす(時間短縮用)(再生タイプを設定)
VOID DRAW_MESSAGE(int);

PlayerStates Pstates;
EnemyStates Estates;
LOAD_SINGLE_IMAGE title;
LOAD_SINGLE_IMAGE titlelogo;
LOAD_SINGLE_IMAGE Bplayer;
LOAD_SINGLE_IMAGE enemy;
LOAD_SINGLE_IMAGE btbk;
LOAD_SINGLE_IMAGE UIback;
BATTLE_EFFECT BEnorAT;
BATTLE_EFFECT BEIAI, BEKIKON, BEMAGIC, BEKEN;
CREATE_FONTHANDLE tanu20,tanu20n,tanu30,tanu30n;
MAP_DIV divmap;//マップチップ分割用クラス
MAPINPUT MAPUND;//下のマップ
MAPINPUT MAPMID;//中のマップ
MAPINPUT MAPON;//上のマップ
MAP_HITBOX MAPHIT;//当たり判定のマップ
MAP_ENEMY MAPEN;//敵の出現マップ
//ENEMY Senemy;
CHARA player;
BATTLE_UI UI;
STATES_UI S_UI;
START_UI F_UI;
DEFAULT_COLOR C;
EVENT eventS;
ITEM item;
MUSIC PlayBGM;
MUSIC BTBGM1;
MUSIC BTSEnor;
MUSIC BTSEENnor;
MUSIC BTcar, BTenter;
MUSIC OverBGM;
MUSIC TitleBGM;

int GameScene;//ゲームシーンを管理する
int Message;//メッセージを管理
//攻撃速度の判定をするか否かの関数
int Battleflag = 0;
int BEskillflg = 0;
//0の時自分が攻撃　１の時敵が攻撃
int Playerflag = 0;
//行動後の処理
int Playendflag = 0;
//敵の行動処理
int Enemyflag = 0;
//スキルの行動処理
int skillflag = 0;
int choiceskillflag = 0;
int ENdefflg = 0;
BOOL NowLvUPflg=FALSE;
//ステータス画面のスイッチ分で使用するフラグ
int categori = 0;
int cateprocess = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
/*	SetWindowIconID(IDI_ICON1);*/							//アイコンファイルを読込

	

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	if (LOADING_FULL_IMAGE() == FALSE) { return -1; }//全ての画像を読み込む
	if (LOADING_FULL_MUSIC() == FALSE) { return -1; }//全ての音楽を読み込む
	SetMouseDispFlag(TRUE);			//マウスカーソルを表示
	LOADING_FULL_MAP();				//マップを読み込む関数
	CREATE_FULL_FONT();				//フォントを作成する関数

	GameScene = GAME_PLAY_SCENE;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	eventS.INPUTTXT(EVENT_TXT);
	//start位置の設定
	player.image.x = divmap.width*15; player.image.y =divmap.height*11 ;
	player.Nowhandle = player.image.Divhandle[0];
	UI.UIx[0] = UI.SpotUIx;
	Pstates.INPUT_STATES(PLAYER_STATES);
	Pstates.IAI.INPUT_SKILL(PLAYER_SKILL_IAI_DATA);
	Pstates.IAI.REGISTER_SKILL();
	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了
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
			case GAME_STATES_SCENE:
				MY_STATES(); //ステータス画面
				break;
		}
		//MY_FPS_DRAW();		//FPSの処理[描画]
		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
		//MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	DxLib_End();
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
	F_UI.C_count++;
	F_UI.E_count++;
	if (CheckSoundMem(TitleBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, TitleBGM.handle);	//50%の音量にする
		PlaySoundMem(TitleBGM.handle, DX_PLAYTYPE_LOOP);
	}

	if (CheckHitKey(KEY_INPUT_UP) == TRUE && F_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		if (F_UI.tag <= 0) {
			F_UI.tag = 0;
		}
		else
		{
			F_UI.C_count = 0;
			F_UI.tag -= 1;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && F_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		if (F_UI.tag >=1) {
			F_UI.tag = 1;
		}
		else
		{
			F_UI.C_count = 0;
			F_UI.tag += 1;
		}
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(TitleBGM.handle) != 0)
		{
			StopSoundMem(TitleBGM.handle);
		}
		PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
		GameScene = GAME_PLAY_SCENE;
	}

	return;
}
VOID MY_START_DRAW()
{
	DrawGraph(title.x, title.y, title.handle, TRUE);
	DrawGraph(titlelogo.x, 150, titlelogo.handle, TRUE);
	int Nsize=GetDrawStringWidthToHandle("はじめから",11,tanu30n.handle);
	DrawFormatStringToHandle(GAME_WIDTH/2-Nsize/2, 400, C.Black, tanu30n.handle, "はじめから");
	int Lsize = GetDrawStringWidthToHandle("つづきから", 11, tanu30n.handle);
	DrawFormatStringToHandle(GAME_WIDTH / 2 - Lsize / 2, 500, C.Black, tanu30n.handle, "つづきから");
	DrawFormatStringToHandle(0, 0, C.White, tanu30n.handle, "*画像は開発中のものです（本編では差し替えます）");
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
	S_UI.S_count++;
	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);	//50%の音量にする
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE &&S_UI.CHECK_CHENGE_COUNT_STorPLY()==TRUE )//ステータス画面に移動
	{
		S_UI.S_count = 0;
		GameScene = GAME_STATES_SCENE;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE && S_UI.CHECK_CHENGE_COUNT_STorPLY() == TRUE)//ステータス画面に移動
	{
		S_UI.S_count = 0;
		GameScene = GAME_EVENT_SCENE;
	}
	//プレイヤーの当たり判定を設定
	player.coll.left = player.image.x+5;
	player.coll.top = player.image.y+5;
	player.coll.right = player.image.x + player.image.width-5;
	player.coll.bottom = player.image.y + player.image.height-5;

	//移動前のプレイヤーの場所を取得
	player.OldX = player.image.x;
	player.OldY = player.image.y;
	if (CheckHitKey(KEY_INPUT_UP) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[10];
		player.coll.top -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else{ player.image.y -= 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;}
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
					MAPEN.y[tate][yoko] += 5;
					MAPEN.Hitmap[tate][yoko].bottom += 5;
					MAPEN.Hitmap[tate][yoko].top += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		/*player.image.x -= 5;*/
		player.Nowhandle = player.image.Divhandle[4];
		player.coll.left -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else {
			player.image.x -= 5;
		}
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
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
					MAPEN.x[tate][yoko] += 5;
					MAPEN.Hitmap[tate][yoko].left += 5;
					MAPEN.Hitmap[tate][yoko].right += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[1];
		player.coll.bottom += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else { player.image.y += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
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
					MAPEN.y[tate][yoko] -= 5;
					MAPEN.Hitmap[tate][yoko].bottom -= 5;
					MAPEN.Hitmap[tate][yoko].top -= 5;
				}
			}
		}

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[7];
		player.coll.right += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else { player.image.x += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;}
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
					MAPEN.x[tate][yoko] -= 5;
					MAPEN.Hitmap[tate][yoko].left -= 5;
					MAPEN.Hitmap[tate][yoko].right -= 5;
				}
			}
		}
	}
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x > GAME_WIDTH-divmap.width) { player.image.x = GAME_WIDTH - divmap.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y > GAME_HEIGHT - divmap.height) { player.image.y = GAME_HEIGHT - divmap.height; }
	return;
}

VOID MY_PLAY_DRAW()
{
	SetDrawBright(255, 255, 255);
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
		//for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		//{
		//	DrawGraph(
		//		MAPEN.x[tate][yoko],
		//		MAPEN.y[tate][yoko],
		//		divmap.handle[MAPEN.kind[tate][yoko]],
		//		TRUE);
		//}
	}
//	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
//{
//	for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
//	{
//		//壁ならば
//		if (MAPHIT.kind[tate][yoko] == 63)
//		{
//			DrawBox(MAPHIT.Hitmap[tate][yoko].left, MAPHIT.Hitmap[tate][yoko].top,
//				MAPHIT.Hitmap[tate][yoko].right, MAPHIT.Hitmap[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
//		}
//
//	}
//}
//	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
	return;
}

VOID MY_STATES()
{
	MY_STATES_PROC();
	MY_STATES_DRAW();
	return;
}

VOID MY_STATES_PROC()
{
	//0=ステータス画面
	//1=セーブ画面

	switch (categori)
	{
	case 0:
		//プレイ画面とステータス画面を切り替える
		S_UI.S_count++;
		S_UI.C_count++;
		if ((CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) && S_UI.CHECK_CHENGE_COUNT_STorPLY() == TRUE)
		{
			S_UI.S_count = 0;
			GameScene = GAME_PLAY_SCENE;
		}
		//カテゴリの枠を変える
		if ((CheckHitKey(KEY_INPUT_RIGHT) == TRUE) && S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
		{
			S_UI.Ctag += 1;
			S_UI.C_count = 0;
			if (S_UI.Ctag >= 4)
			{
				S_UI.Ctag = 4;
			}
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == TRUE && S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
		{
			S_UI.Ctag -= 1;
			S_UI.C_count = 0;
			if (S_UI.Ctag <= 0)
			{
				S_UI.Ctag = 0;
			}
		}
		if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)//エンターを押すとカテゴリ内の処理へ移動
		{
			S_UI.S_count=0;
			S_UI.C_count=0;
			if (S_UI.Ctag == 0) {};
			if (S_UI.Ctag == 1) { categori = 1; cateprocess = 1; }//セーブ処理へ
		}
		break;
	case(1):
		switch(cateprocess)
		{
		case(1)://セーブ処理
			S_UI.C_count++;
			if (CheckHitKey(KEY_INPUT_DOWN)==TRUE && S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
			{
				if (S_UI.Savetag > 2) { S_UI.Savetag = 2; }
				else {
					S_UI.C_count = 0;
					S_UI.Savetag++;
				}
			}
			if (CheckHitKey(KEY_INPUT_UP)==TRUE && S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
			{
				if (S_UI.Savetag < 0) { S_UI.Savetag = 0; }
				else {
					S_UI.C_count = 0;
					S_UI.Savetag--;
				}
			}
			if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
			{
				if(S_UI.Savetag == 0)
				{
					Pstates.SAVE_STATES(PLAYER_SAVE_SLOT0);
				}
				if (S_UI.Savetag == 1)
				{
					Pstates.SAVE_STATES(PLAYER_SAVE_SLOT1);
				}
				if (S_UI.Savetag == 2)
				{
					Pstates.SAVE_STATES(PLAYER_SAVE_SLOT2);
				}
			}
		}
		break;
	}

	return;
}
VOID MY_STATES_DRAW()
{
	float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
	float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;
	float c= ((float)Pstates.EXP / (float)Pstates.EXPMAX) * 300;
	int Color = GetColor(255, 255, 255);
	DrawGraph(0, 0, S_UI.back.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(15, 80, S_UI.back2.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	DrawGraph(15, 15, S_UI.UIimg.UIhandle[0], TRUE);
	DrawGraph(252, 15, S_UI.UIimg.UIhandle[1], TRUE);
	DrawGraph(488, 15, S_UI.UIimg.UIhandle[2], TRUE);
	DrawGraph(725, 15, S_UI.UIimg.UIhandle[3], TRUE);
	switch (categori)
	{
	case(0):
		if (S_UI.Ctag == 0)
		{
			DrawGraph(GAME_WIDTH - S_UI.charaimg.width - 20, 124 - 5,
				S_UI.charaimg.handle, TRUE);
			DrawBox(S_UI.STallx - 2, S_UI.STallx - 2, S_UI.STallx + 100 + 2, 80 + 2, GetColor(255, 255, 255), TRUE);
			DrawBox(S_UI.STallx, S_UI.STallx, S_UI.STallx + (int)a, 80, GetColor(0, 255, 0), TRUE);
			DrawFormatStringToHandle(S_UI.STallx, 90
				, Color, tanu30n.handle, "狐耳族:%s", Pstates.Name);
			DrawFormatStringToHandle(S_UI.STallx, 90
				, Color, tanu20n.handle, "Lv %4d", Pstates.Lv);
			DrawFormatStringToHandle(S_UI.STallx, 130
				, Color, tanu20n.handle, "HP %d/%d", Pstates.HP, Pstates.HPMAX);
			DrawFormatStringToHandle(S_UI.STallx, 170
				, Color, tanu20n.handle, "MP %d/%d", Pstates.MP, Pstates.MPMAX);
			DrawFormatStringToHandle(S_UI.STallx, 210
				, Color, tanu20n.handle, "物理攻撃力 %d(+%d)", Pstates.AT, Pstates.STR);
			DrawFormatStringToHandle(S_UI.STallx, 250
				, Color, tanu20n.handle, "物理防御力 %d", Pstates.DF);
			DrawFormatStringToHandle(S_UI.STallx, 290
				, Color, tanu20n.handle, "魔法防御力 %d", Pstates.MDF);
			DrawFormatStringToHandle(S_UI.STallx, 330
				, Color, tanu20n.handle, "すばやさ %d", Pstates.AGI);
			DrawFormatStringToHandle(S_UI.STallx, 370
				, Color, tanu20n.handle, "次のレベルまで %dExp", Pstates.EXPMAX - Pstates.EXP);
			DrawBox(S_UI.STallx - 2, 405 - 2, S_UI.STallx + 300 + 2, 410 + 2, GetColor(255, 255, 255), TRUE);
			DrawBox(S_UI.STallx, 405, S_UI.STallx + (int)c, 410, GetColor(0, 255, 0), TRUE);
		}
		break;
	case(1):
		break;
	}
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
	eventS.count++;
	if (eventS.count > eventS.countMax)
	{
		if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
		{
			eventS.strLnum+=3;
			eventS.count = 0;
		}
	}
	return;
}
VOID MY_EVENT_DRAW()
{
	MY_PLAY_DRAW(); //プレイ画面を描画する
	DrawGraph(0,GAME_HEIGHT-190, eventS.txtUI.handle, TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 120, GetColor(255, 255, 255),
		tanu30.handle,eventS.str[eventS.strLnum],  TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 90, GetColor(255, 255, 255),
		tanu30.handle, eventS.str[eventS.strLnum+1], TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 60, GetColor(255, 255, 255),
		tanu30.handle, eventS.str[eventS.strLnum+2], TRUE);
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
	if (CheckSoundMem(BTBGM1.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BTBGM1.handle);	//50%の音量にする
		PlaySoundMem(BTBGM1.handle, DX_PLAYTYPE_LOOP);
	}
	Pstates.AT = Pstates.STR;
	UI.CHANGE_COUNT();

	if (UI.Mssgcount > UI.MssgcntMx)//エンカウント時のメッセージ
	{
		UI.EncntUIisView = FALSE;
	}
	if (UI.EncntUIisView == TRUE)
	{
		UI.Mssgcount++;
	}
	else
	{
		switch (Battleflag)
		{
		case 0://プレイヤーの行動
			switch (Playerflag)
			{
			case 0://行動選択の処理
				if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
				{
					PLAY_CARSOL_SOUND();
					UI.count = 0;
					UI.UIx[UI.UItag] = UI.NonSpotUIx;
					UI.UItag -= 1;
					if (UI.UItag < 0) { UI.UItag = 4; }
					UI.UIx[UI.UItag] = UI.SpotUIx;
				}
				if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
				{
					PLAY_CARSOL_SOUND();
					UI.count = 0;
					UI.UIx[UI.UItag] = UI.NonSpotUIx;
					UI.UItag += 1;
					if (UI.UItag > 4) { UI.UItag = 0; }
					UI.UIx[UI.UItag] = UI.SpotUIx;
				}
				if (UI.UItag == 0) { Message = SELECT_NORMAL_AT; }
				if (UI.UItag == 1) { Message = SELECT_SKILL; }
				if (UI.UItag == 2) { Message = GUARD; }
				if (UI.UItag == 3) { Message = SELECT_ITEM; }
				if (UI.UItag == 4) { Message = RUN; }
				if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)//エンターを押したとき
				{
					PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
					Playerflag = 1;
				}
				break;
			case 1://行動選択時の動作
				switch (UI.UItag)
				{
				case 0://通常攻撃
					switch(BEnorAT.effectflg)
					{ 
					case 0://エフェクト描画箇所
					Message = NORMAL_AT;//メッセージを通常攻撃に
					BEnorAT.isView = TRUE;//BEの描画flgをオン
					BEnorAT.PLAY_SE();//SEを再生
					if (Pstates.DMcalcflg == TRUE)//ダメージ計算を一度だけ行う
					{
						ENdefflg=Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
						//ダメージを計算し、敵を倒したかどうかのフラグを格納(TRUE=int 1)
						Pstates.DMcalcflg = FALSE;//ダメージ計算フラグを無効にする
					}
					BEnorAT.MOVE_VIEW_IMAGE();//画像のアニメーション
					//終了時に次のスイッチに移行＆エフェクト描画変数をすべて初期化
					break;
					case 1:
						Pstates.CRI_MESSAGE(Playerflag, 3,Message);
						break;
					}
					//HPを判定する関数
					break;
				case 1://スキル
					switch (skillflag) {
					case 0:
						UI.ENTER_COUNT_SKILL();
						if (CheckHitKey(KEY_INPUT_BACK) == TRUE)//バックスペースを押したとき
						{
							UI.count = 0;
							UI.Scount = 0;
							Playerflag = 0;
						}
						if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
						{
							if (UI.Skilltag == 0 || UI.Skilltag == 1) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag -= 2;
							}
						}
						if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
						{
							if (UI.Skilltag == 2 || UI.Skilltag == 3) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag += 2;
							}
						}
						if ((CheckHitKey(KEY_INPUT_LEFT) == TRUE) && UI.CHANGE_COUNT() == TRUE)//左を押したとき
						{
							if (UI.Skilltag == 0 || UI.Skilltag == 2) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag -= 1;
							}
						}
						if ((CheckHitKey(KEY_INPUT_RIGHT) == TRUE) && UI.CHANGE_COUNT() == TRUE)//右を押したとき
						{
							if (UI.Skilltag == 1 || UI.Skilltag == 3) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag += 1;
							}
						}
						if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enterを押したとき
						{
							UI.Scount = 0;
							PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
							skillflag = 1;
						}
						break;
					case 1://スキル項目を華麗に移動させる酷く無駄なケース文
						switch (UI.Skilltag)
						{
						case 0:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Iaiy2 -= UI.Iaiy2Move;
							}
							else {
								skillflag = 2;
							}
							break;
						case 1:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.KiKonx2 -= UI.KiKonx2Move;
								UI.KiKonx -= UI.KiKonxMove;
								UI.KiKony2 -= UI.KiKony2Move;
							}
							else { skillflag = 2; }
							break;
						case 2:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Keny -= UI.KenyMove;
								UI.Keny2 -= UI.Keny2Move;
							}
							else { skillflag = 2; }
							break;
						case 3:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Magicx -= UI.MagicxMove;
								UI.Magicx2 -= UI.Magicx2Move;
								UI.Magicy -= UI.MagicyMove;
								UI.Magicy2 -= UI.Magicy2Move;
							}
							else { skillflag = 2; }
							break;
						}
						break;
					case 2:
						switch (UI.Skilltag)
						{
						case 0:
							Message = SKILL_IAI_WAZANAME;
							UI.ENTER_COUNT_SKILL();
							if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
							{
								if (Pstates.IAI.Viewtag==0) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.IAI.Viewtag -= 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
							{
								if (Pstates.IAI.flg[Pstates.IAI.Viewtag+1]==FALSE) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.IAI.Viewtag += 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enterを押したとき
							{
								if (Pstates.MP < Pstates.IAI.mp[Pstates.IAI.Viewtag])
								{
									Message = NOT_ENOUGH_MP;
								}
								else {
									UI.Scount = 0;
									PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
									LOADING_SKILL_IMGandSE(Pstates.IAI.Viewtag,UI.Skilltag);
									//使用するスキルの画像とイメージを取り込む
									skillflag = 3;
								}
							}
							break;
						case 1:
							Message = SKILL_KIKON_WAZANAME;
							UI.ENTER_COUNT_SKILL();
							if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
							{
								if (Pstates.KIKON.Viewtag == 0) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.KIKON.Viewtag -= 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
							{
								if (Pstates.KIKON.flg[Pstates.KIKON.Viewtag + 1] == FALSE) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.KIKON.Viewtag += 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enterを押したとき
							{
								if (Pstates.MP < Pstates.KIKON.mp[Pstates.KIKON.Viewtag])
								{
									Message = NOT_ENOUGH_MP;
								}
								else {
									UI.Scount = 0;
									PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
									LOADING_SKILL_IMGandSE(Pstates.KIKON.Viewtag, UI.Skilltag);
									//使用するスキルの画像とイメージを取り込む
									skillflag = 3;
								}
							}
							break;
						case 2:
							Message = SKILL_KEN_WAZANAME;
							UI.ENTER_COUNT_SKILL();
							if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
							{
								if (Pstates.KEN.Viewtag == 0) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.KEN.Viewtag -= 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
							{
								if (Pstates.KEN.flg[Pstates.KEN.Viewtag + 1] == FALSE) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.KEN.Viewtag += 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enterを押したとき
							{
								if (Pstates.MP < Pstates.KEN.mp[Pstates.KEN.Viewtag])
								{
									Message = NOT_ENOUGH_MP;
								}
								else {
									UI.Scount = 0;
									PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
									LOADING_SKILL_IMGandSE(Pstates.KEN.Viewtag, UI.Skilltag);
									//使用するスキルの画像とイメージを取り込む
									skillflag = 3;
								}
							}
							break;
						case 3:
							Message = SKILL_MAGIC_WAZANAME;
							UI.ENTER_COUNT_SKILL();
							if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//上を押したとき
							{
								if (Pstates.MAGIC.Viewtag == 0) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.MAGIC.Viewtag -= 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//下を押したとき
							{
								if (Pstates.MAGIC.flg[Pstates.MAGIC.Viewtag + 1] == FALSE) {}
								else {
									PLAY_CARSOL_SOUND();
									UI.count = 0;
									Pstates.MAGIC.Viewtag += 1;
								}
							}
							if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enterを押したとき
							{
								if (Pstates.MP < Pstates.MAGIC.mp[Pstates.MAGIC.Viewtag])
								{
									Message = NOT_ENOUGH_MP;
								}
								else {
									UI.Scount = 0;
									PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
									LOADING_SKILL_IMGandSE(Pstates.MAGIC.Viewtag, UI.Skilltag);
									//使用するスキルの画像とイメージを取り込む
									skillflag = 3;
								}
							}
							break;
						}
						break;
					case 3:
						switch (UI.Skilltag)
						{
						case 0://エフェクト描画箇所
							switch (BEIAI.effectflg)
							{
							case 0:
								Message = SKILL_IAI_WAZA_AT;//メッセージを通常攻撃に
								BEIAI.isView = TRUE;//BEの描画flgをオン
								BEIAI.PLAY_SE();//SEを再生
								if (Pstates.DMcalcflg == TRUE)//ダメージ計算を一度だけ行う
								{
									ENdefflg = Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
									//ダメージを計算し、敵を倒したかどうかのフラグを格納(TRUE=int 1)
									Pstates.DMcalcflg = FALSE;//ダメージ計算フラグを無効にする
								}
								BEIAI.MOVE_VIEW_IMAGE();//画像のアニメーション
								//終了時に次のスイッチに移行＆エフェクト描画変数をすべて初期化
								break;
							case 1:
								Pstates.CRI_MESSAGE(Playerflag, 3, Message);
								break;
							}
							break;
						case 1://エフェクト描画箇所
							switch (BEKIKON.effectflg)
							{
							case 0:
								Message = SKILL_KIKON_WAZA_AT;//メッセージを通常攻撃に
								BEKIKON.isView = TRUE;//BEの描画flgをオン
								BEKIKON.PLAY_SE();//SEを再生
								if (Pstates.DMcalcflg == TRUE)//ダメージ計算を一度だけ行う
								{
									ENdefflg = Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
									//ダメージを計算し、敵を倒したかどうかのフラグを格納(TRUE=int 1)
									Pstates.DMcalcflg = FALSE;//ダメージ計算フラグを無効にする
								}
								BEKIKON.MOVE_VIEW_IMAGE();//画像のアニメーション
								//終了時に次のスイッチに移行＆エフェクト描画変数をすべて初期化
								break;
							case 1:
								Pstates.CRI_MESSAGE(Playerflag, 3, Message);
								break;
							}
							break;
						case 2://エフェクト描画箇所
							switch (BEKEN.effectflg)
							{
							case 0:
								Message = SKILL_KEN_WAZA_AT;//メッセージを通常攻撃に
								BEKEN.isView = TRUE;//BEの描画flgをオン
								BEKEN.PLAY_SE();//SEを再生
								if (Pstates.DMcalcflg == TRUE)//ダメージ計算を一度だけ行う
								{
									ENdefflg = Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
									//ダメージを計算し、敵を倒したかどうかのフラグを格納(TRUE=int 1)
									Pstates.DMcalcflg = FALSE;//ダメージ計算フラグを無効にする
								}
								BEKEN.MOVE_VIEW_IMAGE();//画像のアニメーション
								//終了時に次のスイッチに移行＆エフェクト描画変数をすべて初期化
								break;
							case 1:
								Pstates.CRI_MESSAGE(Playerflag, 3, Message);
								break;
							}
							break;
						case 3://エフェクト描画箇所
							switch (BEMAGIC.effectflg)
							{
							case 0:
								Message = SKILL_MAGIC_WAZA_AT;//メッセージを通常攻撃に
								BEMAGIC.isView = TRUE;//BEの描画flgをオン
								BEMAGIC.PLAY_SE();//SEを再生
								if (Pstates.DMcalcflg == TRUE)//ダメージ計算を一度だけ行う
								{
									ENdefflg = Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
									//ダメージを計算し、敵を倒したかどうかのフラグを格納(TRUE=int 1)
									Pstates.DMcalcflg = FALSE;//ダメージ計算フラグを無効にする
								}
								BEMAGIC.MOVE_VIEW_IMAGE();//画像のアニメーション
								//終了時に次のスイッチに移行＆エフェクト描画変数をすべて初期化
								break;
							case 1:
								Pstates.CRI_MESSAGE(Playerflag, 3, Message);
								break;
							}
							break;
						}
						break;

					}
					break;
				case 2://防御
				{
					//現在の防御値を記録
					Pstates.OldbufDF = Pstates.bufDF;
					Pstates.OldbufMDF = Pstates.bufMDF;
					//防御値を倍にする
					Pstates.bufDF = Pstates.bufDF * 3;
					Pstates.bufMDF = Pstates.bufMDF * 3;
					Enemyflag = 1;
					Battleflag = 1;//敵のターンへ
				}
				break;
				case 3://アイテム
					break;
				case 4://逃げる
					Pstates.RUN_AWAY(Estates.AGI);
					if (Pstates.isRun == TRUE)
					{
						Playendflag = 0;
						Playerflag = 2;
					}
					else
					{
						Enemyflag = 0;
						Battleflag = 1;//敵のターンへ
					}
					break;
				}
				break;
			case 2://行動終了時の処理
				switch (Playendflag)
				{
				case 0://逃亡成功時の処理
					UI.BrightR -= 5, UI.BrightG -= 5, UI.BrightB -= 5;
					if (UI.BrightR < 0)
					{
						BATTLE_PROC_NEW();
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGMを止める
						}
						GameScene = GAME_PLAY_SCENE;
					}
					break;
				case 1:
					UI.BrightR -= 5, UI.BrightG -= 5, UI.BrightB -= 5;
					if (UI.BrightR < 0)
					{
						BATTLE_PROC_NEW();
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGMを止める
						}
						GameScene = GAME_PLAY_SCENE;
					}
				}
				break;
			case 3://攻撃時の処理
				if (ENdefflg == 1)//敵を倒したとき
				{
					UI.Endefeatcnt++;
					if (UI.Endefeatcnt < 60)
					{
						Message = DEFEAT_EN;
					}
					else if (UI.Endefeatcnt < 120)
					{
						Message = GET_EXP;
						if (UI.PlusEXPflg == TRUE)//経験値を一度だけ加算する
						{
							Pstates.EXP += Estates.EXP;
							UI.PlusEXPflg = FALSE;
							if (Pstates.EXP >= Pstates.EXPMAX)
							{//経験値の最大値を超えたときレベルアップ関数を動かす
								NowLvUPflg = Pstates.LEVELUP();
							}
						}
					}
					if (120 < UI.Endefeatcnt && NowLvUPflg == TRUE)
					{//レベルアップ時の処理 
						Message = Levelup;
						if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
						{
							Playendflag = 0;
							Playerflag = 2;
						}
					}
					else
					{
						if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
						{
							Playendflag = 0;
							Playerflag = 2;
						}
					}
				}
				else {
					Pstates.criflg = FALSE;
					Pstates.DMcalcflg = TRUE;
					BEnorAT.effectflg = 0;
					BEIAI.effectflg = 0;
					BEKEN.effectflg = 0;
					BEMAGIC.effectflg = 0;
					BEKIKON.effectflg = 0;
					skillflag = 0;
					UI.Skilltag = 0;
					UI.cricnt = 0;
					Playerflag = 0;
					Battleflag = 1;
					UI.SKILL_MOVE_NEW();
				}
				break;
			}
			break;
		case 1://敵の行動
			switch (Enemyflag)
			{
			case 0://通常攻撃
				BEnorAT.Count++;
				if (CheckSoundMem(BTSEENnor.handle) == 0 && BEnorAT.Count > 60)
				{
					//BGMの音量を下げる
					ChangeVolumeSoundMem(255 * 50 / 100, BTSEENnor.handle);	//50%の音量にする
					PlaySoundMem(BTSEENnor.handle, DX_PLAYTYPE_BACK);
					if (Pstates.DAMAGE_CALC(Pstates.bufDF, Pstates.HP) == 1)
					{
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGMを止める
						}
						GameScene = GAME_END_SCENE;
					};
					BEnorAT.Count = 0;
					Battleflag = 0;
					Playerflag = 0;
				}
				break;
			case 1:
				BEnorAT.Count++;
				if (CheckSoundMem(BTSEENnor.handle) == 0 && BEnorAT.Count > 60)
				{
					//BGMの音量を下げる
					ChangeVolumeSoundMem(255 * 50 / 100, BTSEENnor.handle);	//50%の音量にする
					PlaySoundMem(BTSEENnor.handle, DX_PLAYTYPE_BACK);
					if (Pstates.DAMAGE_CALC(Pstates.bufDF, Pstates.HP) == 1) {
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGMを止める
						}
						GameScene = GAME_END_SCENE;
					};
					BEnorAT.Count = 0;
					Pstates.bufDF = Pstates.OldbufDF;
					Pstates.bufMDF = Pstates.OldbufMDF;
					Battleflag = 0;
					Playerflag = 0;
				}
				break;
			}
			break;

		}
	}
	return;
}

VOID MY_BATTLE_DRAW()
{
		int Ename=GetDrawFormatStringWidth("%s", Estates.Name);
		SetDrawBright(UI.BrightR,UI.BrightG,UI.BrightB);//バトル画面の輝度
		DrawGraph(btbk.x, btbk.y, btbk.handle, TRUE);//バトル画面の背景
		
		DrawGraph(enemy.x, 50, enemy.handle, TRUE);//エネミーの画像
		DrawFormatStringToHandle(enemy.x+enemy.width/2-Ename/2, 50, GetColor(255, 255, 255), tanu20.handle,
			"%s", Estates.Name);
		DrawGraph(250, 350, Bplayer.handle, TRUE);
		DrawFormatStringToHandle(250, 370
			, GetColor(255, 255, 255), tanu20.handle, "%s", Pstates.Name);
		/*DrawGraph(player.x, player.y, player.handle, TRUE);*/
		/*DrawBox(20, GAME_HEIGHT - 220, 220, GAME_HEIGHT-55, GetColor(255, 255, 0), TRUE);*/
		//UI
		DrawGraph(20, 370, UIback.handle, TRUE);
		DrawGraph(UI.UIx[0], 380, UI.image.UIhandle[0], TRUE);//攻撃
		DrawGraph(UI.UIx[1], 420, UI.image.UIhandle[1], TRUE);//スキル
		DrawGraph(UI.UIx[2], 460, UI.image.UIhandle[2], TRUE);//防御
		DrawGraph(UI.UIx[3], 500, UI.image.UIhandle[3], TRUE);//アイテム
		DrawGraph(UI.UIx[4], 540, UI.image.UIhandle[4], TRUE);//逃げる

		DrawBox(0, GAME_HEIGHT - 40, GAME_WIDTH, GAME_HEIGHT, GetColor(125, 125, 0), TRUE);
		
		//メッセージボード
		if (UI.EncntUIisView == TRUE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			//GetDrawFormatStringWidthToHandle(tanu30n.handle,
			//	"%s", );
			DrawBox(0, 340, GAME_WIDTH,GAME_HEIGHT,GetColor(200,200,200),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DRAW_MESSAGE(Message);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawBox(0, 340, GAME_WIDTH, 360, GetColor(124, 124, 124), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DRAW_MESSAGE(Message);
		}
		float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
		float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;

		float c = ((float)Estates.HP / (float)Estates.HPMAX) * 100;
		float d = ((float)Estates.MP / (float)Estates.MPMAX) * 100;
		//自分のHP
			DrawBox(350 - 2, 400 - 2, 350 + 100 + 2, 420 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 400, 350 + (int)a, 420, GetColor(0, 255, 95), TRUE);
			DrawFormatStringToHandle(350, 400
				, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.HP, Pstates.HPMAX);
			DrawBox(350 - 2, 425 - 2, 350 + 100 + 2, 445 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 425, 350 + (int)b, 445, GetColor(30, 144, 255), TRUE);
			DrawFormatStringToHandle(350, 425
				, C.White, tanu20.handle, "%d/%d", Pstates.MP, Pstates.MPMAX);
			/*&& UI.UItag == 1)*/
			switch (Playerflag)
			{
			case 1:
				switch(UI.UItag)
				{ 
				case 1:
					switch (skillflag)
					{
					case 0:
						//居合
						UI.SnameIAI = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname);
						DrawBox((int)UI.Iaix - 2, (int)UI.Iaiy - 2, (int)UI.Iaix2 + 2, (int)UI.Iaiy2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Iaix, (int)UI.Iaiy, (int)UI.Iaix2, (int)UI.Iaiy2, GetColor(170, 170, 170), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Iaix2 + (int)UI.Iaix) / 2 - UI.SnameIAI/2,
							((int)UI.Iaiy2+ (int)UI.Iaiy)/2-15
							, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname);
						//煌魂術
						UI.SnameKiKon = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname2);
						DrawBox((int)UI.KiKonx - 2, (int)UI.KiKony - 2, (int)UI.KiKonx2 + 2, (int)UI.KiKony2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.KiKonx, (int)UI.KiKony, (int)UI.KiKonx2, (int)UI.KiKony2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.KiKonx2 + (int)UI.KiKonx)/ 2 - UI.SnameKiKon / 2,
							((int)UI.KiKony2 + (int)UI.KiKony) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname2);
						//剣術
						UI.SnameKen = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname3);
						DrawBox((int)UI.Kenx - 2, (int)UI.Keny - 2, (int)UI.Kenx2 + 2, (int)UI.Keny2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Kenx, (int)UI.Keny, (int)UI.Kenx2, (int)UI.Keny2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Kenx2 + (int)UI.Kenx) / 2 - UI.SnameKen / 2,
							((int)UI.Keny2 + (int)UI.Keny) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname3);
						//魔法
						UI.SnameMagic = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname4);
						DrawBox((int)UI.Magicx - 2, (int)UI.Magicy - 2, (int)UI.Magicx2 + 2, (int)UI.Magicy2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Magicx, (int)UI.Magicy, (int)UI.Magicx2, (int)UI.Magicy2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Magicx2 + (int)UI.Magicx) / 2 - UI.SnameMagic / 2,
							((int)UI.Magicy2 + (int)UI.Magicy) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname4);
						if (UI.Skilltag == 0)
						{
							DrawBox(480 - 2, 400 - 2, 710 + 2, 490 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 1)
						{
							DrawBox(720 - 2, 400 - 2, 950 + 2, 490 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 2)
						{
							DrawBox(480 - 2, 500 - 2, 710 + 2, 590 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 3)
						{
							DrawBox(720 - 2, 500 - 2, 950 + 2, 590 + 2, GetColor(255, 0, 0), FALSE);
						}
						break;
					case 1:
						switch (UI.Skilltag)
						{
						case 0:
								//居合
								DrawBox((int)UI.Iaix - 2, (int)UI.Iaiy - 2, (int)UI.Iaix2 + 2, (int)UI.Iaiy2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Iaix, (int)UI.Iaiy, (int)UI.Iaix2, (int)UI.Iaiy2, GetColor(170, 170, 170), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameIAI / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname);
								break;
						case 1:
								DrawBox((int)UI.KiKonx - 2, (int)UI.KiKony - 2, (int)UI.KiKonx2 + 2, (int)UI.KiKony2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.KiKonx, (int)UI.KiKony, (int)UI.KiKonx2, (int)UI.KiKony2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameKiKon / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname2);
								break;
						case 2:
								DrawBox((int)UI.Kenx - 2, (int)UI.Keny - 2, (int)UI.Kenx2 + 2, (int)UI.Keny2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Kenx, (int)UI.Keny, (int)UI.Kenx2, (int)UI.Keny2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameKen / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname3);
								break;
						case 3:
								DrawBox((int)UI.Magicx - 2, (int)UI.Magicy - 2, (int)UI.Magicx2 + 2, (int)UI.Magicy2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Magicx, (int)UI.Magicy, (int)UI.Magicx2, (int)UI.Magicy2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameMagic / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname4);
								break;
						}
						break;
					case 2:
						switch (UI.Skilltag)
						{
						case 0:
							DrawBox((int)UI.Iaix - 2, (int)UI.Iaiy - 2, (int)UI.Iaix2 + 2, (int)UI.Iaiy2 + 2, GetColor(242, 242, 242), TRUE);
							DrawBox((int)UI.Iaix, (int)UI.Iaiy, (int)UI.Iaix2, (int)UI.Iaiy2, GetColor(170, 170, 170), TRUE);
							DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameIAI / 2, 400
								, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname);
							for(int i=0;i<10;i++)
							{
								if (Pstates.IAI.flg[Pstates.IAI.isView] == 1)
								{
									DrawBox(UI.Iaiskillx - 2, UI.Iaiskilly - 2, UI.Iaiskillx2 + 2, UI.Iaiskilly2 + 2,
										C.Black, TRUE);
									DrawFormatStringToHandle(UI.Iaiskillx, UI.Iaiskilly
										, GetColor(255, 255, 255), tanu20n.handle, "%4s 威力:%3d 消費MP:%2d %s",
										Pstates.IAI.Name[Pstates.IAI.isView]
										, int(Pstates.IAI.hosei[Pstates.IAI.isView] * 100), Pstates.IAI.mp[Pstates.IAI.isView],
										Pstates.IAI.expl[Pstates.IAI.isView]);
									Pstates.IAI.isView++, UI.Iaiskilly += 30, UI.Iaiskilly2 += 30;
								}
							}
							Pstates.IAI.isView=0, UI.Iaiskilly = 435, UI.Iaiskilly2 = 460;
							DrawBox(UI.Iaiskillx - 2, UI.Iaiskilly+(Pstates.IAI.Viewtag*30) - 2,
								UI.Iaiskillx2 + 2, UI.Iaiskilly2+(Pstates.IAI.Viewtag * 30) + 2,
								C.White, FALSE);//選択枠を表示する

							break;
						}
					}
					break;
				}
				break;
			}
		DrawBox(350 - 2, 200 - 2, 350 + 100 + 2, 220 + 2, GetColor(255, 255, 255), TRUE);
		DrawBox(350, 200, 350 + (int)c, 220, GetColor(0, 255, 0), TRUE);
		DrawFormatStringToHandle(350, 200
			, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Estates.HP, Estates.HPMAX);
		if (BEnorAT.isView == TRUE)//通常攻撃のエフェクト　
		{
			DrawGraph(enemy.x, enemy.y,
				BEnorAT.image.Divhandle[BEnorAT.Viewimage], TRUE);
		}
		if (BEIAI.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(enemy.x, enemy.y,
				BEIAI.image.Divhandle[BEIAI.Viewimage], TRUE);
		}
		if (BEKIKON.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(enemy.x, enemy.y,
				BEKIKON.image.Divhandle[BEKIKON.Viewimage], TRUE);
		}
		if (BEKEN.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(enemy.x, enemy.y,
				BEKEN.image.Divhandle[BEKEN.Viewimage], TRUE);
		}
		if (BEMAGIC.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(enemy.x, enemy.y,
				BEMAGIC.image.Divhandle[BEMAGIC.Viewimage], TRUE);
		}

		DrawStringToHandle(320, GAME_HEIGHT - 30, "Enter:決定 十字キー:選択 Return:キャンセル", GetColor(255, 255, 255), tanu20.handle); return;
}



VOID MY_END()
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC()
{
	if (CheckSoundMem(OverBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, OverBGM.handle);	//50%の音量にする
		PlaySoundMem(OverBGM.handle, DX_PLAYTYPE_LOOP);
	}
	return;
}
VOID MY_END_DRAW()
{
	DrawStringToHandle(0, 0, "あなたは負けました", GetColor(255, 255, 255), tanu20.handle);
	return;
}

void BATTLE_FLAG(int PAVI, int EAVI)//速度を比較して先攻後攻を判断する関数
{
	if (PAVI >= EAVI)
	{
		Battleflag = TRUE;//プレイヤーが攻撃
	}
	else
	{
		Battleflag = FALSE;//敵が攻撃
	}
}

VOID BATTLE_PROC_NEW(VOID)//バトルシーンを初期化する関数
{
	Playerflag = 0;
	Playendflag = 0;
	UI.UItag = 0;
	UI.Mssgcount = 0;
	Battleflag = 0;
	Enemyflag = 0;
	skillflag = 0;
	UI.Skilltag = 0;
	UI.EncntUIisView = TRUE;
	BEnorAT.effectflg = 0;				//通常エフェクトの初期化
	BEIAI.effectflg = 0;
	Pstates.criflg = FALSE;				//クリティカルの発生判定を否定に戻す
	Pstates.DMcalcflg = TRUE;			//ダメージ計算の判定を復活
	UI.PlusEXPflg = TRUE;				//EXPの計算をできるように戻す
	UI.LvUPflg = TRUE;					//レベルアップの判定をできるように戻す
	NowLvUPflg = FALSE;					//↑と同じ
	UI.Endefeatcnt = 0;					//敵を倒したときの処理のカウントを初期化する
	Pstates.LvUPBUF_NEW();				//レベルアップの加算値の変数を初期化
	Pstates.cricnt = 0;					//クリティカル判定のカウントを初期化
	UI.UIx[0] = UI.SpotUIx;
	UI.SKILL_MOVE_NEW();
	Message = ENCOUNT;
	for (int i = 1; i < 5; i++)
	{
		UI.UIx[i] = UI.NonSpotUIx;
	}
	return;
}

VOID INPUTBTLSTATES_BUF()//一戦闘用にステータスを退避させる関数
{
	Pstates.bufAT = Pstates.AT;
	Pstates.bufDF = Pstates.DF;
	Pstates.bufMDF = Pstates.MDF;
	Pstates.bufAGI = Pstates.AGI;
	return;
}

BOOL LOADING_FULL_IMAGE(VOID)//画像全てをロードする関数
{
	if (title.LOADING_IMAGE(IMAGE_TITLE) == -1) { return FALSE; }
	if (Bplayer.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return FALSE; }
	/*if (player.image.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == FALSE) { return FALSE; }*/
	if (player.image.LOADING_DIV_IMAGE(DIV_CHARA_TATE, DIV_CHARA_YOKO, MAP_DIV_WIDTH,
		MAP_DIV_HEIGHT, IMAGE_PLAYER_INMAP) == -1) {
		return FALSE;
	}
	if (BEnorAT.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
		DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, IMAGE_BATTLE_EFFECT_NORMAL_AT) == -1)
	{
		return FALSE;
	}
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return FALSE; }
	if (btbk.LOADING_IMAGE(IMAGE_BATTLE_BACK) == -1) { return FALSE; }
	if (UIback.LOADING_IMAGE(IMAGE_UI_BACK) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_KOUGEKI, 0) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_SKILL, 1) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_GUARD, 2) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_ITEM, 3) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_RUN, 4) == -1) { return FALSE; }
	//スタート画面
	if (titlelogo.LOADING_IMAGE(IMAGE_START_ROGO) == -1) { return FALSE; }
	//ステータス画面
	if (S_UI.charaimg.LOADING_IMAGE(IMAGE_STATES_CHARA) == -1) { return FALSE; }
	if (S_UI.UIimg.LOADING_IMAGE(IMAGE_STATES_UI_ST, 0) == -1) { return FALSE; }
	if (S_UI.UIimg.LOADING_IMAGE(IMAGE_STATES_UI_ITEM, 1) == -1) { return FALSE; }
	if (S_UI.UIimg.LOADING_IMAGE(IMAGE_STATES_UI_SAVE, 2) == -1) { return FALSE; }
	if (S_UI.UIimg.LOADING_IMAGE(IMAGE_STATES_UI_LOAD, 3) == -1) { return FALSE; }
	if (S_UI.back.LOADING_IMAGE(IMAGE_STATES_BACK) == -1) { return FALSE; }
	if (S_UI.back2.LOADING_IMAGE(IMAGE_STATES_BACK2) == -1) { return FALSE; }
	//イベント画面
	if (eventS.txtUI.LOADING_IMAGE(IMAGE_EVENT_TXTUIBACK) == -1) { return FALSE; }
	return TRUE;
}

VOID LOADING_FULL_MAP()
{
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
	return;
}

VOID CREATE_FULL_FONT()
{
	tanu20.CREATE_FONT(20, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu20n.CREATE_FONT_NONEDGE(20, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30.CREATE_FONT(30, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30n.CREATE_FONT_NONEDGE(30, FONT_TANU_PATH, FONT_TANU_NAME);
	return;
}

BOOL LOADING_FULL_MUSIC()
{
	if (TitleBGM.LOAD_MUSIC(TITLE_SCENE_MUSIC) == FALSE) { return -1; }
	if (PlayBGM.LOAD_MUSIC(PLAY_SCENE_MUSIC) == FALSE) { return -1; }
	if (BTBGM1.LOAD_MUSIC(BATTLE_SCENE_MUSIC1) == FALSE) { return -1; }
	if (BEnorAT.se.LOAD_MUSIC(BATTLE_SE_NORMALAT) == FALSE) { return -1; }//通常攻撃のSE
	//スキル居合の音声読み込み
	if (BEIAI.se.LOAD_MUSIC(BATTLE_SE_HOTAL) == FALSE){return -1; }//スキル蛍火のSE
	if (BTSEENnor.LOAD_MUSIC(BATTLE_SE_EN_NORMAL_AT) == FALSE) { return -1; }
	if (OverBGM.LOAD_MUSIC(END_SCENE_MUSIC_OVER) == FALSE) { return -1; }
	if (BTcar.LOAD_MUSIC(BATTLE_SE_CARSOL) == FALSE) { return -1; }
	if (BTenter.LOAD_MUSIC(BATTLE_SE_ENTER) == FALSE) { return -1; }
	return TRUE;
}

BOOL LOADING_SKILL_IMGandSE(int skillNum,int skilltag)
{
	switch (skilltag) {
	case 0:
		BEIAI.LOADING_PATH(skillNum);
		if (BEIAI.se.LOAD_MUSIC(BEIAI.sepath) == FALSE) { return FALSE; }//選択されたスキルの読み込み
		if (BEIAI.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
			DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, BEIAI.imgpath) == -1)
		{
			return FALSE;
		}
		return TRUE;
		break;
	case 1:
		BEKIKON.LOADING_PATH(skillNum);
		if (BEKIKON.se.LOAD_MUSIC(BEKIKON.sepath) == FALSE) { return FALSE; }//選択されたスキルの読み込み
		if (BEKIKON.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
			DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, BEKIKON.imgpath) == -1)
		{
			return FALSE;
		}
		return TRUE;
		break;
	case 2:
		BEKEN.LOADING_PATH(skillNum);
		if (BEKEN.se.LOAD_MUSIC(BEKEN.sepath) == FALSE) { return FALSE; }//選択されたスキルの読み込み
		if (BEKEN.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
			DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, BEKEN.imgpath) == -1)
		{
			return FALSE;
		}
		return TRUE;
		break;
	case 3:
		BEMAGIC.LOADING_PATH(skillNum);
		if (BEMAGIC.se.LOAD_MUSIC(BEMAGIC.sepath) == FALSE) { return FALSE; }//選択されたスキルの読み込み
		if (BEMAGIC.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
			DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, BEMAGIC.imgpath) == -1)
		{
			return FALSE;
		}
		return TRUE;
		break;
	}
}

VOID PLAY_CARSOL_SOUND()
{
	ChangeVolumeSoundMem(255 * 50 / 100, BTcar.handle);	//50%の音量にする
	PlaySoundMem(BTcar.handle, DX_PLAYTYPE_BACK);
	return;
}

VOID PLAY_ENTER_SOUND(int playtype)
{
	ChangeVolumeSoundMem(255 * 50 / 100, BTenter.handle);	//50%の音量にする
	PlaySoundMem(BTenter.handle, playtype);
	return;
}

VOID DRAW_MESSAGE(int mestype)
{
	switch (mestype)
	{
	case ENCOUNT:
		DrawFormatStringToHandle(0, 340, GetColor(255, 255, 255), tanu20.handle,
			"%sがあらわれた！", Estates.Name);
		return;
		break;
	case SELECT_NORMAL_AT:
		DrawStringToHandle(0, 340, "通常攻撃を行います", C.White, tanu20.handle);
		return;
		break;
	case NORMAL_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sのこうげき！", Pstates.Name);
		return;
		break;
	case SELECT_SKILL:
		DrawStringToHandle(0, 340, "スキルを選択して攻撃します", C.White, tanu20.handle);
		return;
		break;
	case GUARD:
		DrawStringToHandle(0, 340, "攻撃をせずに防御します", C.White, tanu20.handle);
		return;
		break;
	case SELECT_ITEM:
		DrawStringToHandle(0, 340, "アイテムを選択して使用します", C.White, tanu20.handle);
		return;
		break;
	case RUN:
		DrawStringToHandle(0, 340, "走ってこの場から逃げます。失敗することも…", C.White, tanu20.handle);
		return;
		break;
	case CRITICAL:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"急所を突いた！ %sに%dのダメージ",Estates.Name,Pstates.damage);
		return;
		break;
	case DEFEAT_EN:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sを倒した！", Estates.Name);
		return;
		break;
	case GET_EXP:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%d経験値を獲得", Estates.EXP);
		return;
		break;
	case GIVE_DAMAGE:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sに%dのダメージ", Estates.Name,Pstates.damage);
		return;
		break;
	case Levelup:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"レベルが%d上がった！HP+%d MP+%d 攻撃力+%d 魔法攻撃力+%d すばやさ+%d 防御力+%d 魔法防御力+%d",
			Pstates.bLv, Pstates.bHPMAX, Pstates.bMPMAX, Pstates.bSTR, Pstates.bMSTR,
			Pstates.bAGI,Pstates.bDF,Pstates.bMDF);
		return;
		break;
	case NOT_ENOUGH_MP:
		DrawStringToHandle(0, 340, "MPが足りません", C.White, tanu20.handle);
		return;
		break;
	case SKILL_IAI_WAZANAME:
		char buf[100] = { "" };
		strcpy(buf, Pstates.IAI.expl[Pstates.IAI.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_KIKON_WAZANAME:
		char buf[100] = { "" };
		strcpy(buf, Pstates.KIKON.expl[Pstates.KIKON.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_MAGIC_WAZANAME:
		char buf[100] = { "" };
		strcpy(buf, Pstates.MAGIC.expl[Pstates.MAGIC.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_KEN_WAZANAME:
		char buf[100] = { "" };
		strcpy(buf, Pstates.KEN.expl[Pstates.KEN.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_IAI_WAZA_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
		"%sの%s!",Pstates.Name,Pstates.IAI.bufName[Pstates.IAI.Viewtag]);
		return;
		break;
	case SKILL_KIKON_WAZA_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sの%s!", Pstates.Name, Pstates.KIKON.bufName[Pstates.KIKON.Viewtag]);
		return;
		break;
	case SKILL_MAGIC_WAZA_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sの%s!", Pstates.Name, Pstates.MAGIC.bufName[Pstates.MAGIC.Viewtag]);
		return;
		break;
	case SKILL_KEN_WAZA_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sの%s!", Pstates.Name, Pstates.KEN.bufName[Pstates.KEN.Viewtag]);
		return;
		break;
	}
}