#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include "font.hpp"
#include "map.hpp"
#include "player.hpp"
#include "hitbox.hpp"
#include "battleUI.hpp"
#include "enemystatas.hpp"
#include "playerstatus.hpp"
#include "BATTLEEFFECT.hpp"
#include "mykey_input.hpp"
#include "Item.hpp"
#include "music.hpp"
#include "StatesUI.hpp"
#include "startUI.hpp"
#include "event.hpp"
#include "WaitTimer.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "ChangingTime.hpp"

using namespace std;

#define MOVE_MAP_UP 5
#define MOVE_MAP_LEFT 5
#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

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

VOID MY_LOAD_MAP(VOID);			//イベント画面
VOID MY_LOAD_MAP_PROC(VOID);		//イベント画面の処理
VOID MY_LOAD_MAP_DRAW(VOID);		//イベント画面の描画

VOID BATTLE_PROC_NEW(VOID);		//バトルシーンを初期化する関数
BOOL LOADING_FULL_IMAGE(VOID);	//画像全てをロードする関数
VOID LOADING_SAMPLE_MAP(VOID);	//マップを読み込む関数
VOID LOADING_VILLAGE_MAP(VOID);	//村マップを読み込む関数
VOID LOADING_FOREST_MAP(VOID);	//森マップを読み込む関数
VOID CREATE_FULL_FONT(VOID);	//フォントを作成する関数
BOOL LOADING_FULL_MUSIC(VOID);	//音楽を読み込む関数
BOOL LOADING_SKILL_IMGandSE(int,int); //スキル使用時にSEと画像を読み込む
VOID INPUTBTLSTATES_BUF(VOID);	//1戦闘用にステータスを退避させる関数
VOID PLAY_CARSOL_SOUND(VOID);	//カーソル音を鳴らす(時間短縮用)
VOID PLAY_ENTER_SOUND(int);	//決定音を鳴らす(時間短縮用)(再生タイプを設定)
VOID DRAW_MESSAGE(int);
VOID RESIZING_SAMPLE_MAP(VOID);
VOID RESIZING_VILLAGE_MAP(VOID);
VOID RESIZING_FOREST_MAP(VOID);
BOOL LOADING_FOREST_COORDINATES(VOID);
BOOL LOADING_DATA_SLOT(int); //セーブスロットからデータをロードする


PlayerStates Pstates;
EnemyStates Estates;
LOAD_SINGLE_IMAGE title, over, clear;
LOAD_SINGLE_IMAGE titlelogo;
LOAD_SINGLE_IMAGE Bplayer;
LOAD_SINGLE_IMAGE enemy;
LOAD_SINGLE_IMAGE btbk;
LOAD_SINGLE_IMAGE UIback;
BATTLE_EFFECT BEnorAT;
BATTLE_EFFECT BEIAI, BEKIKON, BEMAGIC, BEKEN;
CREATE_FONTHANDLE tanu20, tanu20n, tanu30, tanu30n, tanu80;
MAP_DIV divmap;//マップチップ分割用クラス
MAPINPUT MAPUND,MAPMID,MAPON;//マップ
MAP_HITBOX MAPHIT,MAPLIGHT;//当たり判定のマップ
MAP_ENEMY MAPEN;//敵の出現マップ
//ENEMY Senemy;
CHARA player;
BATTLE_UI UI;
STATES_UI S_UI;
START_UI F_UI;
DEFAULT_COLOR C;
EVENT eventS;
ITEM item;
MUSIC PlayBGM, Encount;
MUSIC BTBGM1;
MUSIC BTSEnor;
MUSIC BTSEENnor;
MUSIC BTcar, BTenter;
MUSIC OverBGM, ClearBGM;
MUSIC TitleBGM;
CHANGE_TIME ChangeT;
KEYINPUT KEY;
WaitingTime WaiTime;
SINGLE_TASK Item_Task;

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

int TATE_MAX = 0;
int YOKO_MAX = 0;

BOOL GAME_END_CLEAR;
BOOL LAST_BOSS=FALSE;

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
/*	RESIZING_SAMPLE_MAP();
	LOADING_SAMPLE_MAP();*/				//マップを読み込む関数
	RESIZING_VILLAGE_MAP();//村マップ
	LOADING_VILLAGE_MAP();

	CREATE_FULL_FONT();				//フォントを作成する関数

	GameScene = GAME_START_SCENE;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	eventS.INPUTTXT(EVENT_TXT);
	//start位置の設定
	player.image.x = divmap.width*15; player.image.y =divmap.height*11 ;
	player.Nowhandle = player.image.Divhandle[0];
	UI.UIx[0] = UI.SpotUIx;
	Pstates.INPUT_STATES(PLAYER_STATES);
	Pstates.IAI.INPUT_SKILL(PLAYER_SKILL_IAI_DATA);
	Pstates.IAI.REGISTER_SKILL();
	//仮データ
	Pstates.bufLOADINGDATA(0, PLAYER_SAVE1_PSTATUS, PLAYER_SAVE1_PLAYTIME);
	Pstates.PLAYTIME_STATE();
	MAPUND.LOADING_MAP_TAG(0, MAP_TAG_1);

	item.INPUTITEM_HEAL(ITEM_FILE_PATH);
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
			case GAME_LOAD_MAP_SCENE:
				MY_LOAD_MAP(); //マップをロードする画面
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
	if (CheckSoundMem(TitleBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, TitleBGM.handle);	//50%の音量にする
		PlaySoundMem(TitleBGM.handle, DX_PLAYTYPE_LOOP);
	}
	//はじめからとつづきからを選ぶ
	switch (F_UI.Startflg)
	{
	case 0:
		switch (F_UI.Movelogoflg)
		{
		case 0:
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
			{
				if (F_UI.tag == 0) {
					F_UI.tag = 1;
				}
				else
				{
					F_UI.tag -= 1;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0)
			{
				if (F_UI.tag == 1) {
					F_UI.tag = 0;
				}
				else
				{
					F_UI.tag += 1;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)
			{
				if (F_UI.tag == 0)
				{
					if (CheckSoundMem(TitleBGM.handle) != 0)
					{
						StopSoundMem(TitleBGM.handle);
					}
					PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
					Pstates.PLAYTIME_CALC_F();
					GameScene = GAME_PLAY_SCENE;
				}
				if (F_UI.tag == 1)
				{
					PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
					F_UI.Movelogoflg = 1;
				}
			}
			break;
		case 1:
			if (titlelogo.y > 20)
			{
				titlelogo.y -= 2;
			}
			else {
				F_UI.Startflg = 1;
			}
			break;
		}
		break;
	case 1:
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
		{
			if (F_UI.DataTag == 0) { F_UI.DataTag = 2; }
			else { F_UI.DataTag--; }
		}
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0)
		{
			if (F_UI.DataTag == 2) { F_UI.DataTag = 0; }
			else { F_UI.DataTag++; }
		}
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)
		{
			if (F_UI.DataTag == 0&&Pstates.bufFullTime[0]!=0)
			{
				LOADING_DATA_SLOT(MAPUND.MAPtag[0]);
				Pstates.INPUT_PLAYER_PLACE(player.image.x, player.image.y, PLAYER_SAVE1_PLACE);
				if (CheckSoundMem(TitleBGM.handle) != 0)
				{
					StopSoundMem(TitleBGM.handle);
				}
				PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
				Pstates.PLAYTIME_CALC_F();
				GameScene = GAME_PLAY_SCENE;
			}
			if (F_UI.DataTag == 1 && Pstates.bufFullTime[1] != 0)
			{
				LOADING_DATA_SLOT(MAPUND.MAPtag[1]);
				Pstates.INPUT_PLAYER_PLACE(player.image.x, player.image.y, PLAYER_SAVE2_PLACE);
				if (CheckSoundMem(TitleBGM.handle) != 0)
				{
					StopSoundMem(TitleBGM.handle);
				}
				PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
				GameScene = GAME_PLAY_SCENE;
			}
			if (F_UI.DataTag == 2 && Pstates.bufFullTime[2] != 0)
			{
				LOADING_DATA_SLOT(MAPUND.MAPtag[2]);
				Pstates.INPUT_PLAYER_PLACE(player.image.x, player.image.y, PLAYER_SAVE3_PLACE);
				if (CheckSoundMem(TitleBGM.handle) != 0)
				{
					StopSoundMem(TitleBGM.handle);
				}
				PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
				GameScene = GAME_PLAY_SCENE;
			}
		}
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_BACK) == 0)
		{
			F_UI.Startflg = 2;
		}
		if(F_UI.DataTag==0)
		{
			F_UI.Carsolx = F_UI.SaveData1x, F_UI.Carsolx2 = F_UI.SaveData1x2,
			F_UI.Carsoly = F_UI.SaveData1y, F_UI.Carsoly2 = F_UI.SaveData1y2;
		}
		if (F_UI.DataTag == 1)
		{
			F_UI.Carsolx = F_UI.SaveData1x, F_UI.Carsolx2 = F_UI.SaveData1x2,
			F_UI.Carsoly = F_UI.SaveData2y, F_UI.Carsoly2 = F_UI.SaveData2y2;
		}
		if (F_UI.DataTag == 2)
		{
			F_UI.Carsolx = F_UI.SaveData1x, F_UI.Carsolx2 = F_UI.SaveData1x2,
			F_UI.Carsoly = F_UI.SaveData3y, F_UI.Carsoly2 = F_UI.SaveData3y2;
		}
		break;
	case 2:
		if (titlelogo.y < 150)
		{
			titlelogo.y += 2;
		}
		else {
			F_UI.DataTag = 0;
			F_UI.tag = 0;
			F_UI.Movelogoflg = 0;
			F_UI.Startflg = 0;
		}
		break;
	}

	return;
}
VOID MY_START_DRAW()
{
	DrawGraph(title.x, title.y, title.handle, TRUE);
	DrawGraph(titlelogo.x, titlelogo.y, titlelogo.handle, TRUE);
	switch (F_UI.Startflg) {
	case 0:
		if (F_UI.tag == 0)
		{
			int Nsize = GetDrawStringWidthToHandle("はじめから", 11, tanu30n.handle);
			DrawFormatStringToHandle(GAME_WIDTH / 2 - Nsize / 2, 400, C.Black, tanu30n.handle, "はじめから");
			int Lsize = GetDrawStringWidthToHandle("つづきから", 11, tanu20n.handle);
			DrawFormatStringToHandle(GAME_WIDTH / 2 - Lsize / 2, 500, C.Black, tanu20n.handle, "つづきから");
		}
		if (F_UI.tag == 1)
		{
			int Nsize = GetDrawStringWidthToHandle("はじめから", 11, tanu20n.handle);
			DrawFormatStringToHandle(GAME_WIDTH / 2 - Nsize / 2, 400, C.Black, tanu20n.handle, "はじめから");
			int Lsize = GetDrawStringWidthToHandle("つづきから", 11, tanu30n.handle);
			DrawFormatStringToHandle(GAME_WIDTH / 2 - Lsize / 2, 500, C.Black, tanu30n.handle, "つづきから");
		}
		break;
	case 1:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,220);
		DrawBox(F_UI.SaveData1x, F_UI.SaveData1y, F_UI.SaveData1x2, F_UI.SaveData1y2, C.White, TRUE);
		DrawBox(F_UI.SaveData1x, F_UI.SaveData2y, F_UI.SaveData1x2, F_UI.SaveData2y2, C.White, TRUE);
		DrawBox(F_UI.SaveData1x, F_UI.SaveData3y, F_UI.SaveData1x2, F_UI.SaveData3y2, C.White, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		DrawBox(F_UI.Carsolx, F_UI.Carsoly, F_UI.Carsolx2, F_UI.Carsoly2, C.Red, FALSE);

		if (Pstates.bufFullTime[0] == 0)
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
		}
		else
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData1y + 5, C.Black, tanu30n.handle, "セーブデータ1");
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 70, C.Black, tanu20n.handle, "プレイ時間%02d:%02d:%02d", 
				Pstates.bhour[0], Pstates.bminutes[0],Pstates.bsecond[0]);
		}

		if (Pstates.bufFullTime[1] == 0)
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
		}
		else
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData2y + 5, C.Black, tanu30n.handle, "セーブデータ2");
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
		}

		if (Pstates.bufFullTime[2] == 0)
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
		}
		else
		{
			DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData3y + 5, C.Black, tanu30n.handle, "セーブデータ3");
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
			DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
		}
		break;
	}
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

	//セーブ画面表示のためにデータを読み込む
	/*Pstates.bufLOADINGDATA(0, PLAYER_SAVE1_PSTATUS, PLAYER_SAVE1_PLAYTIME);*/



	switch (categori)
	{
	case 0:
		//プレイ画面とステータス画面を切り替える
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_ESCAPE)==0)
		{
			GameScene = GAME_PLAY_SCENE;
		}
		//カテゴリの枠を変える
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RIGHT) == 0)
		{
			S_UI.Ctag += 1;
			if (S_UI.Ctag >= 3)
			{
				S_UI.Ctag = 3;
			}
		}
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_LEFT) == 0)
		{
			S_UI.Ctag -= 1;
			if (S_UI.Ctag <= 0)
			{
				S_UI.Ctag = 0;
			}
		}
		if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)//エンターを押すとカテゴリ内の処理へ移動
		{
			if (S_UI.Ctag == 0) {};
			if (S_UI.Ctag == 1) { categori = 1; cateprocess = 1; }
			if (S_UI.Ctag == 2) { categori = 1; cateprocess = 2; }//セーブ処理へ
		}
		//カーソルの位置を移動
		if (S_UI.Ctag == 0) { S_UI.CarsolX = S_UI.StatusX, S_UI.CarsolX2 = S_UI.StatusX2; }
		if (S_UI.Ctag == 1) { S_UI.CarsolX = S_UI.ItemX, S_UI.CarsolX2 = S_UI.ItemX2; }
		if (S_UI.Ctag == 2) { S_UI.CarsolX = S_UI.SaveX, S_UI.CarsolX2 = S_UI.SaveX2; }
		if (S_UI.Ctag == 3) { S_UI.CarsolX = S_UI.LoadX, S_UI.CarsolX2 = S_UI.LoadX2; }
		break;
	case 1:
		switch (cateprocess)
		{
		case 1:
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0)
			{
				if (S_UI.Itemtag ==ITEMNUM-2||S_UI.Itemtag == ITEMNUM-1){}
				else
				{
					S_UI.ICarsolY += 30, S_UI.ICarsolY2 += 30;
					S_UI.Itemtag += 2;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
			{
				if (S_UI.Itemtag ==0|| S_UI.Itemtag == 1){}
				else
				{
					S_UI.ICarsolY -= 30, S_UI.ICarsolY2 -= 30;
					S_UI.Itemtag -= 2;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_LEFT) == 0)
			{
				if (S_UI.Itemtag % 2 != 0)
				{
					S_UI.ICarsolX -= 300, S_UI.ICarsolX2 -= 300;
					S_UI.Itemtag -= 1;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RIGHT) == 0)
			{
				if (S_UI.Itemtag % 2 == 0)
				{
					S_UI.ICarsolX += 300, S_UI.ICarsolX2 += 300;
					S_UI.Itemtag += 1;
				}
			}
			if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_BACK) == 0)
			{
				S_UI.ICarsolX = 45, S_UI.ICarsolY = 95;
				S_UI.ICarsolX2 = 45+275, S_UI.ICarsolY2 = 125;
				S_UI.Itemtag = 0;
				categori = 0;
			}

			break;
		case 2://セーブ処理
			switch (S_UI.SavingStch)
			{
			case 0:
				if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0)
				{
					if (S_UI.Savetag > 2) { S_UI.Savetag = 2; }
					else {
						S_UI.Savetag++;
					}
				}
				if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
				{
					if (S_UI.Savetag < 0) { S_UI.Savetag = 0; }
					else {
						S_UI.Savetag--;
					}
				}
				if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)//セーブする
				{
					if (S_UI.Savetag == 0)
					{
						Pstates.SAVE_STATES(PLAYER_SAVE1_PSTATUS);
						Pstates.SAVE_PLAYTIME(PLAYER_SAVE1_PLAYTIME,0);
						Pstates.SAVE_PLAYER_PLACE(player.image.x, player.image.y, PLAYER_SAVE1_PLACE);
						MAPUND.SAVE_MAP(TATE_MAX, YOKO_MAX, MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1, MAP_TAG_1);
						S_UI.SavingStch = 1;
					}
					if (S_UI.Savetag == 1)
					{
						/*Pstates.SAVE_STATES(PLAYER_SAVE2_PSTATUS);*/
					}
					if (S_UI.Savetag == 2)
					{
					}
				}
				break;
			case 1:
				
				break;
			}
			break;
		}
		break;
	case 2:
		switch (S_UI.CataEndtag)
		{
		case 2:
			break;
		}
	}

	return;
}
VOID MY_STATES_DRAW()
{
	float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
	float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;
	float c = ((float)Pstates.EXP / (float)Pstates.EXPMAX) * 300;
	int Color = GetColor(255, 255, 255);
	DrawGraph(0, 0, S_UI.back.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(15, 80, S_UI.back2.handle, TRUE);
	DrawBox(S_UI.StatusX, S_UI.UIY, S_UI.StatusX2, S_UI.UIY2, GetColor(255, 0, 0), TRUE);
	DrawBox(S_UI.ItemX, S_UI.UIY, S_UI.ItemX2, S_UI.UIY2, GetColor(255, 0, 0), TRUE);
	DrawBox(S_UI.SaveX, S_UI.UIY, S_UI.SaveX2, S_UI.UIY2, GetColor(255, 0, 0), TRUE);
	DrawBox(S_UI.LoadX, S_UI.UIY, S_UI.LoadX2, S_UI.UIY2, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatStringToHandle(10 + 30, 15 + 13, C.White, tanu30n.handle, "ステータス");
	DrawFormatStringToHandle(10 + 220 + 20 + 45, 15 + 13, C.White, tanu30n.handle, "アイテム");
	DrawFormatStringToHandle(10 + 440 + 40 + 60, 15 + 13, C.White, tanu30n.handle, "セーブ");
	DrawFormatStringToHandle(10 + 660 + 60 + 60, 15 + 13, C.White, tanu30n.handle, "ロード");

	DrawBox(S_UI.CarsolX, S_UI.CarsolY, S_UI.CarsolX2, S_UI.CarsolY2, C.White, FALSE);
	switch (categori)
	{
	case 0:
		switch (S_UI.Ctag)
		{
		case 0://ステータス
			DrawGraph(GAME_WIDTH - S_UI.charaimg.width - 20, 124 - 5,
				S_UI.charaimg.handle, TRUE);

			DrawFormatStringToHandle(S_UI.STallx, 90
				, Color, tanu30n.handle, "狐耳族:%s", Pstates.Name);
			DrawFormatStringToHandle(S_UI.STallx, 130
				, Color, tanu20n.handle, "Lv %4d", Pstates.Lv);

			DrawBox(S_UI.STallx + 100, 160, S_UI.STallx + 100 + 2 + 100, 180, GetColor(255, 255, 255), TRUE);
			DrawBox(S_UI.STallx + 2 + 100, 160 + 2, S_UI.STallx + (int)a - 2 + 100, 180 - 2, C.HPColorN, TRUE);

			DrawFormatStringToHandle(S_UI.STallx, 160
				, Color, tanu20n.handle, "HP %d/%d", Pstates.HP, Pstates.HPMAX);

			DrawBox(S_UI.STallx + 100, 190, S_UI.STallx + 100 + 2 + 100, 210, GetColor(255, 255, 255), TRUE);
			DrawBox(S_UI.STallx + 2 + 100, 190 + 2, S_UI.STallx + (int)b - 2 + 100, 210 - 2, C.MPColor, TRUE);

			DrawFormatStringToHandle(S_UI.STallx, 190
				, Color, tanu20n.handle, "MP %d/%d", Pstates.MP, Pstates.MPMAX);
			DrawFormatStringToHandle(S_UI.STallx, 220
				, Color, tanu20n.handle, "物理攻撃力 %d(+%d)", Pstates.AT, Pstates.STR);
			DrawFormatStringToHandle(S_UI.STallx + 200, 220
				, Color, tanu20n.handle, "魔法攻撃力 %d(+%d)", Pstates.MAT, Pstates.MSTR);
			DrawFormatStringToHandle(S_UI.STallx, 250
				, Color, tanu20n.handle, "物理防御力 %d", Pstates.DF);
			DrawFormatStringToHandle(S_UI.STallx + 200, 250
				, Color, tanu20n.handle, "魔法防御力 %d", Pstates.MDF);
			DrawFormatStringToHandle(S_UI.STallx, 280
				, Color, tanu20n.handle, "すばやさ %d", Pstates.AGI);
			DrawFormatStringToHandle(S_UI.STallx, 310
				, Color, tanu20n.handle, "次のレベルまで %dExp", Pstates.EXPMAX - Pstates.EXP);
			DrawBox(S_UI.STallx - 2, 335 - 2, S_UI.STallx + 300 + 2, 340 + 2, GetColor(255, 255, 255), TRUE);
			DrawBox(S_UI.STallx, 335, S_UI.STallx + (int)c, 340, C.HPColorN, TRUE);
			break;
		case 1://アイテム
			for (int i = 0; i < ITEMNUM; i++)
			{
				if (i % 2 == 0)//偶数の時
				{
					DrawFormatStringToHandle(S_UI.ItemPosX, S_UI.ItemPosY, Color, tanu20n.handle, "%s",
						item.Name[i]);
					DrawFormatStringToHandle(S_UI.ItemPosX+200, S_UI.ItemPosY, Color, tanu20n.handle, "x %3d",
						item.have[i]);
				}
				else {
					DrawFormatStringToHandle(S_UI.ItemPosX + 300, S_UI.ItemPosY, Color, tanu20n.handle, "%s",
						item.Name[i]);
					DrawFormatStringToHandle(S_UI.ItemPosX + 200+300, S_UI.ItemPosY, Color, tanu20n.handle, "x %3d",
						item.have[i]);
					S_UI.ItemPosY += 30;
				}
			}
			S_UI.ItemPosY = 100;
			break;
		case 2://セーブ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData1y, F_UI.SaveData1x2, F_UI.SaveData1y2, C.White, TRUE);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData2y, F_UI.SaveData1x2, F_UI.SaveData2y2, C.White, TRUE);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData3y, F_UI.SaveData1x2, F_UI.SaveData3y2, C.White, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


			DrawBox(F_UI.Carsolx, F_UI.Carsoly, F_UI.Carsolx2, F_UI.Carsoly2, C.Red, FALSE);
			if (Pstates.bufFullTime[0] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData1y + 5, C.Black, tanu30n.handle, "セーブデータ1");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 70, C.Black, tanu20n.handle, "プレイ時間%02d:%02d:%02d",
					Pstates.bhour[0], Pstates.bminutes[0], Pstates.bsecond[0]);
			}

			if (Pstates.bufFullTime[1] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData2y + 5, C.Black, tanu30n.handle, "セーブデータ2");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
			}

			if (Pstates.bufFullTime[2] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData3y + 5, C.Black, tanu30n.handle, "セーブデータ3");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
			}
			break;
		case 3:
			break;
		}
		break;
	case 1:
		switch (cateprocess)
		{
		case 1:
			for (int i = 0; i < ITEMNUM; i++)
			{
				if (i % 2 == 0)//偶数の時
				{
					DrawFormatStringToHandle(S_UI.ItemPosX, S_UI.ItemPosY, Color, tanu20n.handle, "%s",
						item.Name[i]);
					DrawFormatStringToHandle(S_UI.ItemPosX + 200, S_UI.ItemPosY, Color, tanu20n.handle, "x %3d",
						item.have[i]);
				}
				else {
					DrawFormatStringToHandle(S_UI.ItemPosX + 300, S_UI.ItemPosY, Color, tanu20n.handle, "%s",
						item.Name[i]);
					DrawFormatStringToHandle(S_UI.ItemPosX + 200 + 300, S_UI.ItemPosY, Color, tanu20n.handle, "x %3d",
						item.have[i]);
					S_UI.ItemPosY += 30;
				}
			}
			S_UI.ItemPosY = 100;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, S_UI.ItemBrend);

			DrawBox(S_UI.ICarsolX, S_UI.ICarsolY, S_UI.ICarsolX2, S_UI.ICarsolY2, C.White, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawFormatStringToHandle(S_UI.ItemPosX+600, S_UI.ItemPosY, Color, tanu20n.handle, "%s",item.Name[S_UI.Itemtag]);
			DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY+30, C.HPColorN, tanu20n.handle, "HP回復量:%3d",
				item.healHP[S_UI.Itemtag]);
			DrawFormatStringToHandle(S_UI.ItemPosX + 600+150, S_UI.ItemPosY + 30, C.MPColor, tanu20n.handle, "MP回復量:%3d",
				item.healMP[S_UI.Itemtag]);
			DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY + 60, C.BufColor, tanu20n.handle, "バフ効果: %s",
				item.goodStatus[S_UI.Itemtag]);
			DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY + 80, C.DeBufColor, tanu20n.handle, "デバフ効果: %s",
				item.badStatus[S_UI.Itemtag]);
			DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY + 110, Color, tanu20n.handle, "売値:%4d銭\n買値:%4d銭",
				item.sell[S_UI.Itemtag], item.buy[S_UI.Itemtag]);
			for (int i = 0; i < 5; i++)
			{
				DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY + 160, Color, tanu20n.handle, "%s",
					item.Expl[S_UI.Itemtag][i]);
				S_UI.ItemPosY += 25;
			}
			S_UI.ItemPosY -= 25*5;
			/*DrawFormatStringToHandle(S_UI.ItemPosX + 600, S_UI.ItemPosY+30, Color, tanu20n.handle, "%s", item.Expl[S_UI.Itemtag]);*/
			S_UI.ChengingBrend_Item();
			break;
		case 2:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData1y, F_UI.SaveData1x2, F_UI.SaveData1y2, C.White, TRUE);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData2y, F_UI.SaveData1x2, F_UI.SaveData2y2, C.White, TRUE);
			DrawBox(F_UI.SaveData1x, F_UI.SaveData3y, F_UI.SaveData1x2, F_UI.SaveData3y2, C.White, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawBox(F_UI.Carsolx, F_UI.Carsoly, F_UI.Carsolx2, F_UI.Carsoly2, C.Red, FALSE);
			if (Pstates.bufFullTime[0] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData1y + 5, C.Black, tanu30n.handle, "セーブデータ1");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData1y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
			}

			if (Pstates.bufFullTime[1] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData2y + 5, C.Black, tanu30n.handle, "セーブデータ2");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData2y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
			}

			if (Pstates.bufFullTime[2] == 0)
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "セーブデータがありません");
			}
			else
			{
				DrawFormatStringToHandle(F_UI.SaveData1x + 10, F_UI.SaveData3y + 5, C.Black, tanu30n.handle, "セーブデータ3");
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 40, C.Black, tanu20n.handle, "%s Lv:%d", Pstates.Name, Pstates.bufLLv[0]);
				DrawFormatStringToHandle(F_UI.SaveData1x + 30, F_UI.SaveData3y + 70, C.Black, tanu20n.handle, "プレイ時間%d", Pstates.bufFullTime[0]);
			}
			break;
		}
		break;
	}
	return;
}


VOID MY_LOAD_MAP()
{
	MY_LOAD_MAP_PROC();
	MY_LOAD_MAP_DRAW();
	return;
}

VOID MY_LOAD_MAP_PROC()
{
	RESIZING_FOREST_MAP();//森マップ
	LOADING_FOREST_MAP();
	player.image.x = divmap.width * 7; player.image.y = divmap.height * 20;
	GameScene = GAME_PLAY_SCENE;
	return;
}

VOID MY_LOAD_MAP_DRAW()
{
	//DrawStringToHandle(0,0,"ロード中…",C.White,tanu30n.handle);
	//WaitTimer(1000);
	
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
	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);	//50%の音量にする
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}

	if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_ESCAPE)==0)//ステータス画面に移動
	{
		GameScene = GAME_STATES_SCENE;
	}

	if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)//イベント画面に移動
	{
		GameScene = GAME_EVENT_SCENE;
	}
	//プレイヤーの当たり判定を設定
	player.coll.left = player.image.x+5;
	player.coll.top = player.image.y+25;
	player.coll.right = player.image.x + player.image.width-5;
	player.coll.bottom = player.image.y + player.image.height;

	//移動前のプレイヤーの場所を取得
	player.OldX = player.image.x;
	player.OldY = player.image.y;
	if (CheckHitKey(KEY_INPUT_UP) == TRUE)
	{
		player.MOVE_CHARA_CHIP_UP();
		player.Nowhandle = player.image.Divhandle[player.charahandle];
		player.coll.top -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll,TATE_MAX,YOKO_MAX,GameScene) == TRUE){}
		else{ player.image.y -= 5; }
		int ENEMY_COLL = MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX);
		if (ENEMY_COLL== 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG(ChangeT.NowHours);
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;
			}
		if (ENEMY_COLL == 2)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			PlaySoundMem(Encount.handle, DX_PLAYTYPE_BACK);
			if (BTBGM1.LOAD_MUSIC(BATTLE_SCENE_MUSIC_BOSS) == FALSE);
			if (btbk.LOADING_IMAGE(IMAGE_BATTLE_BACK_NUMA) == FALSE);
			LAST_BOSS = TRUE;
			Estates.ENEMY_BOSS_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			while (CheckSoundMem(Encount.handle) == 1) {}
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.y[0][0] < 0 && player.image.y < 100)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
					MAPLIGHT.y[tate][yoko] += 5;
					MAPLIGHT.Hitmap[tate][yoko].bottom += 5;
					MAPLIGHT.Hitmap[tate][yoko].top += 5;
				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		player.MOVE_CHARA_CHIP_LEFT();
		player.Nowhandle = player.image.Divhandle[player.charahandle];
		player.coll.left -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX, GameScene) == TRUE)
		{}
		else {
			player.image.x -= 5;
		}
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG(ChangeT.NowHours);
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.x[0][0] < 0 && player.image.x < 150)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
					MAPLIGHT.x[tate][yoko] += 5;
					MAPLIGHT.Hitmap[tate][yoko].left += 5;
					MAPLIGHT.Hitmap[tate][yoko].right += 5;
				}
			}
		}
	}

	if (KEY.KEYINPUT_NORMAL(KEY_INPUT_DOWN)==0)
	{
		player.MOVE_CHARA_CHIP_DOWN();
		player.Nowhandle = player.image.Divhandle[player.charahandle];
		player.coll.bottom += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX, GameScene) == TRUE)
		{}
		else { player.image.y += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG(ChangeT.NowHours);
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.y[TATE_MAX - 1][0] > GAME_HEIGHT && player.image.y > 500)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
					MAPLIGHT.y[tate][yoko] -= 5;
					MAPLIGHT.Hitmap[tate][yoko].bottom -= 5;
					MAPLIGHT.Hitmap[tate][yoko].top -= 5;
				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		player.MOVE_CHARA_CHIP_RIGHT();
		player.Nowhandle = player.image.Divhandle[player.charahandle];
		player.coll.right += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX, GameScene) == TRUE){}
		else { player.image.x += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll, TATE_MAX, YOKO_MAX) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGMを止める
			}
			Estates.ENEMY_KIND_FLAG(ChangeT.NowHours);
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;}
		if (MAPON.x[0][YOKO_MAX - 1] > GAME_WIDTH && player.image.x > 650)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
					MAPLIGHT.x[tate][yoko] -= 5;
					MAPLIGHT.Hitmap[tate][yoko].left -= 5;
					MAPLIGHT.Hitmap[tate][yoko].right -= 5;
				}
			}
		}
	}
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x > GAME_WIDTH-divmap.width) { player.image.x = GAME_WIDTH - divmap.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y > GAME_HEIGHT - divmap.height) { player.image.y = GAME_HEIGHT - divmap.height; }
	MAPMID.INTARACTIV_MAP(TATE_MAX, YOKO_MAX);
	return;
}

VOID MY_PLAY_DRAW()
{
	SetDrawBright(255, 255, 255);
	for (int tate = 0; tate < TATE_MAX; tate++)//プレイヤーより下のマップ描画
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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

		}
	}
	//if (player.image.IsDraw == TRUE)
	//{
		DrawGraph(player.image.x, player.image.y, player.Nowhandle, TRUE);
/*	}*///プレイヤーの描画
	for (int tate = 0; tate < TATE_MAX; tate++)//プレイヤーより上のマップ描画
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{

			DrawGraph(
				MAPON.x[tate][yoko],
				MAPON.y[tate][yoko],
				divmap.handle[MAPON.kind[tate][yoko]],
				TRUE);
		}
	}
	ChangeT.ChangingLight();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, int(ChangeT.Alpha));
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT,
		GetColor(int(ChangeT.R), int(ChangeT.G), ChangeT.B), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, int(ChangeT.DarkAlpha));
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT,
		GetColor(int(ChangeT.nR), int(ChangeT.nG), ChangeT.nB), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//灯りの描画
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
				DrawGraph(
					MAPLIGHT.x[tate][yoko],
					MAPLIGHT.y[tate][yoko],
					divmap.handle[MAPLIGHT.kind[tate][yoko]],
					TRUE);
		}
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
				if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN)==0)//エンターを押したとき
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
					switch (UI.UseItemflg)
					{
					case 0:
						Message = ITEM_VIEW_NAME;
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RIGHT) == 0)
						{
							if (UI.Itemtag % 2 == 0)
							{
								UI.Itemtag += 1;
								UI.ICarsolX += 260, UI.ICarsolX2 += 260;
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_LEFT) == 0)
						{
							if (UI.Itemtag % 2 != 0)
							{
								UI.Itemtag -= 1;
								UI.ICarsolX -= 260, UI.ICarsolX2 -= 260;
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
						{
							if (UI.Itemtag == 0 || UI.Itemtag == 1)
							{
							}
							else {
								UI.Itemtag -= 2;
								UI.ICarsolY -= 30, UI.ICarsolY2 -= 30;
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0)
						{
							if (UI.Itemtag == ITEMNUM - 2 || UI.Itemtag == ITEMNUM - 1)
							{}
							{
								UI.Itemtag += 2;
								UI.ICarsolY += 30, UI.ICarsolY2 += 30;
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)
						{
							Message = ITEM_WITCH_USE;
							UI.UseItemflg = 1;
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_BACK) == 0)
						{
							UI.Itemtag = 0;
							UI.ICarsolX = 478, UI.ICarsolX2 = 480 + 210 + 2;
							UI.ICarsolY = 398, UI.ICarsolY2 = 400 + 22;
							Playerflag = 0;
						}
						break;
					case 1:
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RIGHT) == 0 ||
							KEY.KEYINPUT_ALLACTION(KEY_INPUT_DOWN) == 0 ||
							KEY.KEYINPUT_ALLACTION(KEY_INPUT_LEFT) == 0 ||
							KEY.KEYINPUT_ALLACTION(KEY_INPUT_UP) == 0)
						{
							Message = ITEM_WITCH_USE;
							PLAY_CARSOL_SOUND();
							if (UI.UseItemtagPorE == 0)
							{
								UI.CharaCarsolX = Estates.image.x, UI.CharaCarsolY = 50;
								UI.CharaCarsolX2 = Estates.image.x + Estates.image.width;
								UI.CharaCarsolY2 = 50+Estates.image.height;
								UI.UseItemtagPorE = 1;
							}
							else
							{
								UI.CharaCarsolX = Bplayer.x, UI.CharaCarsolY = Bplayer.y;
								UI.CharaCarsolX2 = Bplayer.x + Bplayer.width;
								UI.CharaCarsolY2 = Bplayer.y + Bplayer.height;
								UI.UseItemtagPorE = 0;
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_RETURN) == 0)
						{
							PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
							if (UI.UseItemtagPorE == 0)
							{
								if (Item_Task.Single_Task() == TRUE)
								{
								    UI.UseorNot = Pstates.USE_ITEM(item.healHP[UI.Itemtag], item.healMP[UI.Itemtag], item.goodhosei[UI.Itemtag],
									item.badhosei[UI.Itemtag], Pstates.bufAT, Pstates.bufDF, item.have[UI.Itemtag]);
								}
								if (UI.UseorNot == -1)//アイテムが使えない時
								{
									Message = ITEM_NOT_USE;
									if (WaiTime.WaitTime_OneThrough(1) == TRUE)
									{
										WaiTime.WaitTime_New();
										Item_Task.Remove_Task();
									}
								}
								if (UI.UseorNot == 0)//アイテムが使えたとき
								{
									Message = ITEM_USE_MES;
									if (WaiTime.WaitTime_OneThrough(2) == TRUE)
									{
										WaiTime.WaitTime_New();
										Item_Task.Remove_Task();
										UI.UseItemflg = 2;
									}
								}
							}
							else
							{
								if (Item_Task.Single_Task() == TRUE)
								{
									UI.UseorNot = Estates.USE_ITEM(item.healHP[UI.Itemtag], item.healMP[UI.Itemtag], item.goodhosei[UI.Itemtag],
									item.badhosei[UI.Itemtag], Estates.AT, Estates.DF, item.have[UI.Itemtag]);
								}
								if (UI.UseorNot == -1)//アイテムが使えない時
								{
									Message = ITEM_NOT_USE;
									if (WaiTime.WaitTime_OneThrough(1) == TRUE)
									{
										WaiTime.WaitTime_New();
										Item_Task.Remove_Task();
									}
								}
								if (UI.UseorNot == 0)//アイテムが使えたとき
								{
									Message = ITEM_USE_MES;
									if (WaiTime.WaitTime_OneThrough(2) == TRUE)
									{
										WaiTime.WaitTime_New();
										Item_Task.Remove_Task();
										UI.UseItemflg = 2;
									}
								}
							}
						}
						if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_BACK) == 0)
						{
							UI.Itemtag = 0;
							UI.UseItemflg = 0;
							UI.UseItemtagPorE = 0;
						}
						break;
					case 2:
						UI.Itemtag = 0;
						UI.UseorNot = 0;
						UI.UseItemflg = 0;
						UI.UseItemtagPorE = 0;
						UI.UItag = 0;
						Battleflag = 1;
						break;
					}
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
						if (LAST_BOSS == TRUE)
						{
							GAME_END_CLEAR = TRUE;
							GameScene = GAME_END_SCENE;
						}
						else {
							GameScene = GAME_PLAY_SCENE;
						}
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
				switch (UI.EnemyNATflg)
				{
				case 0:
					Message = ENEMY_ATTACK_NORMAL;
					if (WaiTime.WaitTime_OneThrough(1) == TRUE)
					{
						WaiTime.WaitTime_New();
						UI.EnemyNATflg = 1;
					}
					break;
				case 1:
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
						UI.EnemyNATflg = 0;
						Battleflag = 0;
						Playerflag = 0;
					}
					break;
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
						GAME_END_CLEAR = FALSE;
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
		int Ename=GetDrawFormatStringWidth("Lv:%d %s", Estates.Lv, Estates.Name);
		SetDrawBright(UI.BrightR,UI.BrightG,UI.BrightB);//バトル画面の輝度
		DrawGraph(Estates.battleback.x, Estates.battleback.y, Estates.battleback.handle, TRUE);//バトル画面の背景
		
		DrawGraph(Estates.image.x, 50, Estates.image.handle, TRUE);//エネミーの画像
		DrawFormatStringToHandle(Estates.image.x+Estates.image.width/2-Ename/2, 50, GetColor(255, 255, 255), tanu20.handle,
			"Lv:%d %s", Estates.Lv,Estates.Name);//エネミーの名前
		DrawGraph(Bplayer.x,Bplayer.y, Bplayer.handle, TRUE);//プレイヤーの画像
		DrawFormatStringToHandle(250, 370
			, GetColor(255, 255, 255), tanu20.handle, "%s", Pstates.Name);
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
		float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100.0;
		float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100.0;

		//自分のHP
			DrawBox(350 - 2, 400 - 2, 350 + 100 + 2, 420 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 400, 350 + (int)a, 420, C.HPColorN, TRUE);
			DrawFormatStringToHandle(350, 400
				, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.HP, Pstates.HPMAX);
			DrawBox(350 - 2, 425 - 2, 350 + 100 + 2, 445 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 425, 350 + (int)b, 445, C.MPColor, TRUE);
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
				case 3:
					for (int i = 0; i < ITEMNUM; i++)
					{
						if (i % 2 == 0)//偶数の時
						{
							DrawBox(UI.ItemPosX - 2, UI.ItemPosY - 2,
								UI.ItemPosX + 210 + 2, UI.ItemPosY + 22, C.Red, TRUE);
							DrawFormatStringToHandle(UI.ItemPosX, UI.ItemPosY, C.White, tanu20n.handle, "%s",
								item.Name[i]);
							DrawFormatStringToHandle(UI.ItemPosX + 150, UI.ItemPosY, C.White, tanu20n.handle, "x %3d",
								item.have[i]);
						}
						else {
							DrawBox(UI.ItemPosX + 260 - 2, UI.ItemPosY - 2,
								UI.ItemPosX + 260 + 210 + 2, UI.ItemPosY + 22, C.Red, TRUE);
							DrawFormatStringToHandle(UI.ItemPosX + 260, UI.ItemPosY, C.White, tanu20n.handle, "%s",
								item.Name[i]);
							DrawFormatStringToHandle(UI.ItemPosX + 150 + 260, UI.ItemPosY, C.White, tanu20n.handle, "x %3d",
								item.have[i]);
							UI.ItemPosY += 30;
						}
					}
					UI.ChengingBrend_Item();
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, UI.ItemBrend);
					DrawBox(UI.ICarsolX, UI.ICarsolY,
						UI.ICarsolX2, UI.ICarsolY2, C.White, FALSE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					UI.ItemPosY = 400;
					switch (UI.UseItemflg)
					{
					case 0:
						break;
					case 1:
						DrawBox(UI.CharaCarsolX, UI.CharaCarsolY,
							UI.CharaCarsolX2, UI.CharaCarsolY2, C.Red, FALSE);
						break;
					}
					break;
				}
				break;
			}

			float c = ((float)Estates.HP / (float)Estates.HPMAX) * 100.0;
			float d = ((float)Estates.MP / (float)Estates.MPMAX) * 100.0;
		DrawBox(350 - 2, 200 - 2, 350 + 100 + 2, 220 + 2, GetColor(255, 255, 255), TRUE);
		DrawBox(350, 200, 350 + (int)c, 220, GetColor(0, 255, 0), TRUE);
		DrawFormatStringToHandle(350, 200
			, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Estates.HP, Estates.HPMAX);
		if (BEnorAT.isView == TRUE)//通常攻撃のエフェクト　
		{
			DrawGraph(Estates.image.x, Estates.image.y,
				BEnorAT.image.Divhandle[BEnorAT.Viewimage], TRUE);
		}
		if (BEIAI.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(Estates.image.x, Estates.image.y,
				BEIAI.image.Divhandle[BEIAI.Viewimage], TRUE);
		}
		if (BEKIKON.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(Estates.image.x, Estates.image.y,
				BEKIKON.image.Divhandle[BEKIKON.Viewimage], TRUE);
		}
		if (BEKEN.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(Estates.image.x, Estates.image.y,
				BEKEN.image.Divhandle[BEKEN.Viewimage], TRUE);
		}
		if (BEMAGIC.isView == TRUE)//スキルのエフェクト
		{
			DrawGraph(Estates.image.x, Estates.image.y,
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
	if (GAME_END_CLEAR == FALSE)
	{
		if (CheckSoundMem(OverBGM.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, OverBGM.handle);	//50%の音量にする
			PlaySoundMem(OverBGM.handle, DX_PLAYTYPE_LOOP);
		}
	}
	if (GAME_END_CLEAR == TRUE)
	{
		if (CheckSoundMem(ClearBGM.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, ClearBGM.handle);	//50%の音量にする
			PlaySoundMem(ClearBGM.handle, DX_PLAYTYPE_LOOP);
		}
	}
	if (KEY.KEYINPUT_ALLACTION(KEY_INPUT_ESCAPE) == 0)
	{
		if (CheckSoundMem(OverBGM.handle) != 0)
		{
			StopSoundMem(OverBGM.handle);
		}
		GameScene = GAME_START_SCENE;
	}
	return;
}
VOID MY_END_DRAW()
{
	if (GAME_END_CLEAR == FALSE)
	{
		DrawGraph(0, 0, over.handle, TRUE);
		int Font = GetDrawStringWidthToHandle("GAME OVER", 9, tanu80.handle);
		DrawStringToHandle(GAME_WIDTH / 2 - Font / 2, GAME_HEIGHT / 2 - 40, "GAME OVER", C.Red, tanu80.handle);
	}
	if (GAME_END_CLEAR == TRUE)
	{
		DrawGraph(0, 0, clear.handle, TRUE);
		int Font = GetDrawStringWidthToHandle("GAME CLEAR", 9, tanu80.handle);
		DrawStringToHandle(GAME_WIDTH / 2 - Font / 2, GAME_HEIGHT / 2 - 40, "GAME CLEAR", GetColor(0,0,255), tanu80.handle);
	}
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
	UI.Itemtag = 0;
	UI.ICarsolX = 478, UI.ICarsolX2 = 480 + 210 + 2;
	UI.ICarsolY = 398, UI.ICarsolY2 = 400 + 22;
	UI.UseItemflg = 0;
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
	Bplayer.x = 250, Bplayer.y = 350;
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
	if (Estates.battleback.LOADING_IMAGE(IMAGE_BATTLE_BACK) == -1) { return FALSE; }
	if (UIback.LOADING_IMAGE(IMAGE_UI_BACK) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_KOUGEKI, 0) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_SKILL, 1) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_GUARD, 2) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_ITEM, 3) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_RUN, 4) == -1) { return FALSE; }
	//スタート画面
	if (titlelogo.LOADING_IMAGE(IMAGE_START_ROGO) == -1) { return FALSE; }
	titlelogo.y = 150;
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
	//ゲームオーバー画面
	if (over.LOADING_IMAGE(IMAGE_GAME_OVER) == -1) { return FALSE; }
	if (clear.LOADING_IMAGE(IMAGE_GAME_CLEAR) == -1) { return FALSE; }
	return TRUE;
}

VOID RESIZING_VILLAGE_MAP()
{
	MAPHIT.RESIZING_HITBOX(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPEN.RESIZING_HITBOX(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPLIGHT.RESIZING_HITBOX(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPUND.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPMID.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPON.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPHIT.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPEN.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPLIGHT.RESIZE(MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
}

VOID RESIZING_FOREST_MAP()
{
	MAPHIT.RESIZING_HITBOX(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPEN.RESIZING_HITBOX(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPLIGHT.RESIZING_HITBOX(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPUND.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPMID.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPON.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPHIT.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPEN.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPLIGHT.RESIZE(MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
}

VOID LOADING_VILLAGE_MAP()
{
	TATE_MAX =MAP_MURA_TATEMAX , YOKO_MAX = MAP_MURA_YOKOMAX;
	divmap.DIV_MAP(MAP_MURA_PATH, MAP_MURA_DIV_TATE, MAP_MURA_DIV_YOKO, MAP_DIV_WIDTH);
	MAPUND.LOADING_MAP(MAP_MURA_UNDER);//下のマップ
	MAPUND.MAPSETTING(divmap.width, divmap.height,MAP_MURA_STx,MAP_MURA_STy,
		MAP_MURA_TATEMAX,MAP_MURA_YOKOMAX);
	MAPMID.LOADING_MAP(MAP_MURA_MID);//中のマップ
	MAPMID.MAPSETTING(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPON.LOADING_MAP(MAP_MURA_ON);//上のマップ
	MAPON.MAPSETTING(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPHIT.LOADING_MAP(MAP_MURA_HITBOX);//当たり判定のマップ
	MAPHIT.MAPSETTING(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPHIT.SETTING_HITBOX(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX,MAP_MURA_YOKOMAX);
	MAPHIT.HitObj = MAP_MURA_HITOBJ;
	MAPHIT.MVMapHitObj = MAP_MURA_MOVE_HITOBJ;
	MAPEN.LOADING_MAP(MAP_MURA_ENEMYMAP);//敵の出現マップ
	MAPEN.MAPSETTING(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPEN.SETTING_HITBOX(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX,MAP_MURA_YOKOMAX);
	MAPLIGHT.LOADING_MAP(MAP_MURA_LIGHT_HITBOX);//敵の出現マップ
	MAPLIGHT.MAPSETTING(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	MAPLIGHT.SETTING_HITBOX(divmap.width, divmap.height, MAP_MURA_STx, MAP_MURA_STy,
		MAP_MURA_TATEMAX, MAP_MURA_YOKOMAX);
	return;
}

VOID LOADING_FOREST_MAP()
{
	TATE_MAX = MAP_FOREST_TATEMAX, YOKO_MAX = MAP_FOREST_YOKOMAX;
	divmap.DIV_MAP(MAP_FOREST_PATH, MAP_FOREST_DIV_TATE, MAP_FOREST_DIV_YOKO, MAP_DIV_WIDTH);
	MAPUND.LOADING_MAP(MAP_FOREST_UNDER);//下のマップ
	MAPUND.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPMID.LOADING_MAP(MAP_FOREST_MID);//中のマップ
	MAPMID.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPON.LOADING_MAP(MAP_FOREST_ON);//上のマップ
	MAPON.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPHIT.LOADING_MAP(MAP_FOREST_HITBOX);//当たり判定のマップ
	MAPHIT.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPHIT.SETTING_HITBOX(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPHIT.HitObj = MAP_FOREST_HITOBJ;
	MAPEN.LOADING_MAP(MAP_FOREST_ENEMYMAP);//敵の出現マップ
	MAPEN.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPEN.SETTING_HITBOX(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPLIGHT.LOADING_MAP(MAP_FOREST_LIGHT_HITBOX);//灯りの出現マップ
	MAPLIGHT.MAPSETTING(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPLIGHT.SETTING_HITBOX(divmap.width, divmap.height, MAP_FOREST_STx, MAP_FOREST_STy,
		MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX);
	MAPEN.HitObj = MAP_FOREST_ENEMY_HITOBJ;
	MAPEN.HitObjBoss = MAP_FOREST_HITOBJ_BOSS;
	return;
}

BOOL LOADING_FOREST_COORDINATES()
{
	if (MAPUND.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	if (MAPMID.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	if (MAPON.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	if (MAPHIT.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	if (MAPEN.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	if (MAPLIGHT.LOADING_MAP_COORDINATES(MAP_SAVE_PLACE_X_1, MAP_SAVE_PLACE_Y_1) == FALSE) { return FALSE; }
	MAPHIT.SETTING_HITBOX_COORDINATES(divmap.width, divmap.height,MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX,MAP_FOREST_MOVE_HITOBJ);
	MAPEN.SETTING_HITBOX_COORDINATES(divmap.width, divmap.height,MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX,MAP_FOREST_MOVE_HITOBJ);
	MAPLIGHT.SETTING_HITBOX_COORDINATES(divmap.width, divmap.height, MAP_FOREST_TATEMAX, MAP_FOREST_YOKOMAX, MAP_FOREST_MOVE_HITOBJ);
	return TRUE;
}

BOOL LOADING_DATA_SLOT(int maptag)
{
	switch (maptag)
	{
	case 1:
		RESIZING_FOREST_MAP();
		LOADING_FOREST_MAP();
		if (LOADING_FOREST_COORDINATES() == FALSE) { return FALSE; }
		return TRUE;
		break;
	}
}

VOID CREATE_FULL_FONT()
{
	tanu20.CREATE_FONT(20, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu20n.CREATE_FONT_NONEDGE(20, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30.CREATE_FONT(30, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30n.CREATE_FONT_NONEDGE(30, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu80.CREATE_FONT(80, FONT_TANU_PATH, FONT_TANU_NAME);
	return;
}

BOOL LOADING_FULL_MUSIC()
{
	if (TitleBGM.LOAD_MUSIC(TITLE_SCENE_MUSIC) == FALSE) { return -1; }
	if (PlayBGM.LOAD_MUSIC(PLAY_SCENE_MUSIC) == FALSE) { return -1; }
	if (BTBGM1.LOAD_MUSIC(BATTLE_SCENE_MUSIC1) == FALSE) { return -1; }
	if (BEnorAT.se.LOAD_MUSIC(BATTLE_SE_NORMALAT) == FALSE) { return -1; }//通常攻撃のSE
	//スキル居合の音声読み込み
	if (Encount.LOAD_MUSIC(PLAY_BATTLE_CHENGE_SE) == FALSE) { return -1; }
	if (BEIAI.se.LOAD_MUSIC(BATTLE_SE_HOTAL) == FALSE){return -1; }//スキル蛍火のSE
	if (BTSEENnor.LOAD_MUSIC(BATTLE_SE_EN_NORMAL_AT) == FALSE) { return -1; }
	if (OverBGM.LOAD_MUSIC(END_SCENE_MUSIC_OVER) == FALSE) { return -1; }
	if (ClearBGM.LOAD_MUSIC(END_SCENE_MUSIC_CLEAR) == FALSE) { return -1; }
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
	char buf[100] = { "" };

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
		strcpy(buf, Pstates.IAI.expl[Pstates.IAI.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_KIKON_WAZANAME:
		strcpy(buf, Pstates.KIKON.expl[Pstates.KIKON.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_MAGIC_WAZANAME:
		strcpy(buf, Pstates.MAGIC.expl[Pstates.MAGIC.Viewtag]);
		DrawStringToHandle(0, 340, buf, C.White, tanu20.handle);
		return;
		break;
	case SKILL_KEN_WAZANAME:
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
	case ITEM_VIEW_NAME://アイテムの名前を表示する
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"アイテムを選択して使用します 選択アイテム:%s", item.Name[UI.Itemtag]);
		return;
		break;
	case ITEM_USE_MES://アイテムの使用を勧告
		if (UI.UseItemtagPorE == 0)
		{
			DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
				"%sに%sを使った！", Pstates.Name, item.Name[UI.Itemtag]);
		}
		else
		{
			DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
				"%sに%sを投げた！", Estates.Name, item.Name[UI.Itemtag]);
		}
		return;
		break;
	case ITEM_NOT_USE://アイテムのが使えなかったとき
			DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
				"効果がありません");
		return;
		break;
	case ITEM_WITCH_USE://アイテムの相手を選ぶ
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"アイテムを使用する相手を選びます");
		return;
		break;
	case ENEMY_ATTACK_NORMAL://アイテムの相手を選ぶ
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%sのこうげき！",Estates.Name);
		return;
		break;
	}
}