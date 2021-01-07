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
	int uMSTR = 5;
	int uAGI = 6;
	int uDF = 5;
	int uMDF = 5;
	//int uEXP=50;
	int criRan = 100;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT,MSTR,MAT,DF,MDF, AGI, Lv, EXP,EXPMAX;//ステータス
	int bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
	int damage = 0;
	BOOL isRun=FALSE;
	int bufAT, bufDF, bufMDF, bufAGI;//バフ込みのステータス
	int OldbufAT, OldbufDF, OldbufMDF, OldbufAGI;
	float DamageHosei = 1.00;
	//float HPver = ((float)HP / (float)HPMAX) * 100;//HPバーの長さ
	int critical = 100;
	BOOL criflg = FALSE;
	//技
	char skillname[7] = { "居合術" };
	float skillhosei = 1.4;
	//急所に当たる確率が高い
	char skillname2[10] = { "煌魂術" };
	float skillhosei2 = 1.2;
	//確率で相手をやけどにする
	char skillname3[10] = { "剣術" };

	char skillname4[10] = { "魔法" };
	float skillhosei3 = 1.1;
	//二属性のに連撃
	//特殊効果

	//技用の関数
	BOOL SKILL_IAI_MUTUKI(int,int&,int);

	char Name[30] = { "\0" };
	
	BOOL INPUT_STATES(const char*);//ステータスのロード

	BOOL SAVE_STATES(const char*);//ステータスのセーブ

	void CHANGE_SWORD(int,int);//武器の切り替え

	void RUN_AWAY(int);

	BOOL LEVELUP()//レベルアップ関数（途中）
	{
		if (EXP >= EXPMAX)
		{
			while (1)
			{
				if (EXPMAX - EXP >= 0)
				{
					SRand(1);
					int randam = Lv / 10 + 2;
					//上昇量を保存する
					bLv += 1;
					bHPMAX = uHP * Lv / 10 + GetRand(randam);
					bMPMAX += uMP * Lv / 10 + GetRand(randam);
					bSTR += uSTR * Lv / 10 + GetRand(randam);
					bMSTR = uMSTR * Lv / 10 + GetRand(randam);
					bAGI += uAGI * Lv / 10 + GetRand(randam);
					bDF += uDF * Lv / 10 + GetRand(randam);
					bMDF += uMDF * Lv / 10 + GetRand(randam);
					EXP -= EXPMAX;
					EXPMAX = (EXPMAX * 1.1 + Lv + 10) / 2;
				}
				else { break; }
			}
			//上昇量を増分
			Lv += bLv;
			HPMAX += bHPMAX;
			MPMAX += MPMAX;
			STR += STR;
			AGI += AGI;
			DF += DF;
			MDF += MDF;
			return TRUE;
		}
		return FALSE;
	}

	int DAMAGE_CALC(int, int&);//ダメージ計算の関数(相手の防御力,相手のHP)
	int IAI_KITUNEISSOKU_CALC(int, int&);
	int KIKON_HOTAL_CALC(int, int&);
};

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

BOOL PlayerStates::SKILL_IAI_MUTUKI(int bougyo,int& hp,int bufAT)
{
	this->DamageHosei = 1.4;
	int damage = int(((bufAT*bufAT) / (this->AT + bougyo)) * DamageHosei);
	this->DamageHosei = 1.0;
	HP -= damage;
	if (HP <= 0)//HPが０以下の時
	{
		HP = 0;
		return 1;
	}
	return 0;//それ以外の時
}