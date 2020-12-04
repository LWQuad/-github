#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include <iostream>
#include <string>
using namespace std;
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")			//フォントの名前
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

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

class LOAD_SINGLE_IMAGE //画像一枚を読み込むクラス
{
public:
	char path[PATH_MAX];		//パス
	char pathname[PATH_MAX];
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw;				//表示の可否

	BOOL LOADING_IMAGE(const char* pathname)
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
};

class CREATE_FONTHANDLE
{
public:
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ

	BOOL CREATE_FONT(int fontsize,const char* fontpath,const char* fontname)
		//フォントサイズ　フォントのパス　フォントの名前を引数に使用
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

	~CREATE_FONTHANDLE()//フォントハンドルを削除
	{
		DeleteFontToHandle(this->handle);
	}
};

class MUSIC
{
public:

	char path[PATH_MAX];		//パス
	int handle;

	BOOL LOAD_MUSIC(const char* musicpath)
	{
		strcpy_s(path,musicpath);				//パスの設定
		handle = LoadSoundMem(path);			//読み込み
		if (handle == -1)
		{
			//エラーメッセージ表示
			MessageBox(GetMainWindowHandle(), musicpath, "音楽の読み込みに失敗しました", MB_OK);
			return FALSE;
		}
		return TRUE;
	}
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
		int ret;
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
LOAD_SINGLE_IMAGE player;
LOAD_SINGLE_IMAGE enemy;
CREATE_FONTHANDLE tanu20;
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
	if (player.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return -1; }
	SetMouseDispFlag(TRUE);			//マウスカーソルを表示

	GameScene = GAME_BATTLE_SCENE;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

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
	return;
}
VOID MY_PLAY_DRAW()
{
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
	DrawGraph(player.x, player.y, player.handle, TRUE);
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

