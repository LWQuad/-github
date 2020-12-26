#pragma once
#include <iostream>
#define PLAYER_STATES TEXT(".\\STATES\\PlayerStates.csv")

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
	int uAVI = 6;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT,DF,MDF, AGI, Lv, EXP,EXPMAX;
	BOOL isRun=FALSE;

	char Name[10] = { "イロハ\0" };
	
	BOOL INPUT_STATES(const char*);//ステータスのロード

	BOOL SAVE_STATES(const char*);//ステータスのセーブ

	void CHANGE_SWORD(int,int);//武器の切り替え

	void RUN_AWAY(int);

	void LEVELUP()//レベルアップ関数（途中）
	{
		SRand(1);
		int randam = Lv / 10 + 2;
		HP += uHP * Lv / 10 + GetRand(randam);
		return;
	}

	int DAMAGE_CALC(int, int&);
};

BOOL PlayerStates::INPUT_STATES(const char* statespath)//ステータスのロード
{
	int ret;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		&HP, &HPMAX, &MP, &MPMAX, &STR,&DF,&MDF, &AGI,&Lv, &EXP, &EXPMAX) != EOF) {};
	fclose(fp);
	return TRUE;
}

BOOL PlayerStates::SAVE_STATES(const char* statespath)//ステータスのセーブ
{
	FILE* fp = fopen(statespath, "w");
	fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		HP, HPMAX, MP, MPMAX, STR, DF, MDF, AGI, Lv, EXP, EXPMAX);
	fclose(fp);
	return TRUE;
}

int PlayerStates::DAMAGE_CALC(int bougyo, int& HP)//ダメージ計算式
{
	int damage = int((this->AT*AT) / (this->AT + bougyo));
	HP -= damage;
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