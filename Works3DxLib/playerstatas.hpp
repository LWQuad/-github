#pragma once
#include <iostream>
#include <sstream>
#include "BATTLEEFFECT.hpp"
#define PLAYER_STATES TEXT(".\\STATES\\PlayerStates.csv")

#define PLAYER_SAVE_SLOT0 TEXT(".\\SAVEDATA\\SaveDate_slot0.csv")
#define PLAYER_SAVE_SLOT1 TEXT(".\\SAVEDATA\\SaveDate_slot1.csv")
#define PLAYER_SAVE_SLOT2 TEXT(".\\SAVEDATA\\SaveDate_slot2.csv")

#define PLAYER_SKILL_IAI_DATA TEXT(".\\SKILLS\\IAIskill.txt")
enum SKILL_KOUMOKU
{
	sHOSEI,
	sCRIT,
};

class Skill_Management//スキルを管理する関数
{
public:
	//一旦スキルをインプットするバフ変数
	char bufName[10][15] = { "\0" };
	float bufhosei[10] = { 0 };
	float bufcri[10] = { 0 };
	int bufmp[10] = { 0 };
	int flg[10] = { 0 };
	//スキルを表示できるようにする実態変数
	char Name[10][15] = { "\0" };
	float hosei[10] = { 0 };
	float cri[10] = { 0 };
	int mp[10] = { 0 };

	BOOL SAVE_SKILL(const char*);//スキルのセーブ
	BOOL INPUT_SKILL(const char*);//スキルのロード
	BOOL REGISTER_SKILL();//スキルを登録する
};

BOOL Skill_Management::INPUT_SKILL(const char* skillpath)//スキルのロード
{
	int ret, n = 0;
	FILE* fp = fopen(skillpath, "r");
	while (ret = fscanf(fp, "%s,%f,%f,%d,%d,",
		&bufName[n], &bufhosei[n], &bufcri[n], &bufmp[n], &flg[n]) != EOF) {
		n++;
	};
	if (ret == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), skillpath, "スキルデータの読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	fclose(fp);
	return TRUE;
}

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

	//レベルアップ時statesUpの基礎値
	int uHP = 8;
	int uMP = 2;
	int uSTR = 5;
	int uMSTR = 5;
	int uAGI = 6;
	int uDF = 5;
	int uMDF = 5;
	//int uEXP=50;
	int criRan = 100;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT, MSTR, MAT, DF, MDF, AGI, Lv, EXP, EXPMAX;//ステータス
	int bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
	int damage = 0;
	BOOL isRun = FALSE;
	int bufAT, bufDF, bufMDF, bufAGI;//バフ込みのステータス
	int OldbufAT, OldbufDF, OldbufMDF, OldbufAGI;
	float DamageHosei = 1.00;
	//float HPver = ((float)HP / (float)HPMAX) * 100;//HPバーの長さ
	int critical = 10;
	int cricnt = 0;
	BOOL criflg = FALSE;
	//技
	char skillname[7] = { "居合術" };

	//睦月　水無月　神無月　霜月　狐一足　雨水白露　狐返し
	//急所に当たる確率が高い
	char skillname2[10] = { "煌魂術" };
	//蛍火　狐火　灯火煌　不知火　奥義:燐火昏々　狐火宝泉
	float skillhosei2 = 1.2;
	//確率で相手をやけどにする
	char skillname3[10] = { "剣術" };
	//狐表
	char skillname4[10] = { "魔法" };
	//
	float skillhosei3 = 1.1;
	//二属性のに連撃
	//特殊効果


	//技用の関数
	Skill_Management IAI;

	BOOL SKILL_IAI_MUTUKI(int, int&, int);

	char Name[30] = { "\0" };

	BOOL INPUT_STATES(const char*);//ステータスのロード

	BOOL SAVE_STATES(const char*);//ステータスのセーブ

	void CHANGE_SWORD(int, int);//武器の切り替え

	void RUN_AWAY(int);

	BOOL LEVELUP();//レベルアップ関数
	VOID LvUPBUF_NEW();//レベルアップの上昇値の保存変数を初期化
	BOOL DMcalcflg = TRUE;
	int DAMAGE_CALC(int, int&);//ダメージ計算の関数(相手の防御力,相手のHP)
	int SKILL_IAI_CALC(int, int&,int);
	int KIKON_HOTAL_CALC(int, int&);
	VOID CRI_MESSAGE(int&, int,int&);//クリティカルの表示処理(変更する変数,変更するシーン)
};

BOOL Skill_Management::REGISTER_SKILL()//習得済みの技を登録する関数
{
	int N = 0;
	for (int n = 0; n < 10; n++)
	{
		if (flg[n] == 1)//技の習得フラグがTRUEの時
		{
			strcpy(Name[N], bufName[n]);
			hosei[N] = bufhosei[n];
			cri[N] = bufcri[n];
			mp[N] = bufmp[n];
			N++;
		}
	}
	return TRUE;
}

BOOL PlayerStates::INPUT_STATES(const char* statespath)//ステータスのロード
{
	int ret;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
		&HP, &HPMAX, &MP, &MPMAX, &STR,&MSTR,&DF,&MDF, &AGI,&Lv, &EXP, &EXPMAX,&Name) != EOF) {};
	if (ret == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), statespath, "セーブデータの読み込みに失敗しました", MB_OK);
		return FALSE;
	}
	fclose(fp);
	return TRUE;
}



BOOL PlayerStates::SAVE_STATES(const char* statespath)//ステータスのセーブ
{
	FILE* fp = fopen(statespath, "w");
	fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
		HP, HPMAX, MP, MPMAX, STR, MSTR,DF, MDF, AGI, Lv, EXP, EXPMAX,Name);
	fclose(fp);
	return TRUE;
}

int PlayerStates::DAMAGE_CALC(int bougyo, int& HP)//ダメージ計算式
{
	int cri = GetRand(criRan);
	damage = int(((this->AT*AT) / (this->AT + bougyo))*DamageHosei);
	if (cri<critical)
	{
		criflg = TRUE;
		damage = damage * 1.5;
		HP -= damage;
		
	}
	else
	{
		HP -= damage;
	}
	if (HP <= 0)//HPが０以下の時
	{
		HP = 0;
		return 1;
	}
	return 0;//それ以外の時
}


void PlayerStates::CHANGE_SWORD(int oldsword, int newsword)//武器の切り替え
{
	AT -= oldsword;
	AT += newsword;
	return;
}

void PlayerStates::RUN_AWAY(int enemyagi)
{
	if (this->AGI > enemyagi)
	{
		this->isRun = TRUE;
	}
	return;
}

BOOL PlayerStates::SKILL_IAI_CALC(int bougyo,int& hp,int skillnum)
{
	int cri = GetRand(criRan);
	damage = int(((this->AT * AT) / (this->AT + bougyo)) * IAI.hosei[skillnum]);
	if (cri < IAI.cri[skillnum])
	{
		criflg = TRUE;
		damage = damage * 1.5;
		HP -= damage;
	}
	else
	{
		HP -= damage;
	}
	if (HP <= 0)//HPが０以下の時
	{
		HP = 0;
		return 1;
	}
	return 0;//それ以外の時
}

VOID PlayerStates::CRI_MESSAGE(int& sceneflg, int scene,int& Message)
{
	if (this->criflg == TRUE) {//クリティカル発生時
		Message = CRITICAL;
		if (this->cricnt == 1)
		{
			WaitTimer(1000);
			 sceneflg= scene;
		}
		this->cricnt = 1;
	}
	else {
		Message = GIVE_DAMAGE;
		if (this->cricnt == 1)
		{
			WaitTimer(1000);
			sceneflg = scene;
		}
		this->cricnt = 1;
	}
	return;
}

VOID PlayerStates::LvUPBUF_NEW()//レベルアップの上昇値を初期化
{
	bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
}

BOOL PlayerStates::LEVELUP()
{
		if (EXPMAX > EXP) { return FALSE; }
		while (EXPMAX < EXP)
		{
				int randam = 2;
				//上昇量を保存する
				bLv += 1;
				bHPMAX += uHP + GetRand(randam);
				bMPMAX += uMP + GetRand(randam);
				bSTR += uSTR + GetRand(randam);
				bMSTR += uMSTR + GetRand(randam);
				bAGI += uAGI + GetRand(randam);
				bDF += uDF + GetRand(randam);
				bMDF += uMDF + GetRand(randam);
				EXP = EXP - EXPMAX;
				EXPMAX = (int)(EXPMAX * 1.1 + Lv + 10) / 2;
		}
		//上昇量を増分
		Lv += bLv;
		HPMAX += bHPMAX;
		MPMAX += bMPMAX;
		STR += bSTR;
		MSTR += bMSTR;
		AGI += bAGI;
		DF += bDF;
		MDF += bMDF;
		return TRUE;
}