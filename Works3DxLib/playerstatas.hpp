#pragma once
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

	//statesUpの基礎値
	int uHP = 8;
	int uMP = 2;
	int uSTR = 5;
	int uAVI = 6;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT, AVG, Lv, EXP;
	int EXPMAX;

	BOOL INPUT_STATES(const char*);

	BOOL SAVE_STATES(const char*);//ステータスのセーブ


	void LEVELUP()//レベルアップ関数（途中）
	{
		SRand(1);
		int randam = Lv / 10 + 2;
		HP += uHP * Lv / 10 + GetRand(randam);
		return;
	}
};

BOOL PlayerStates::INPUT_STATES(const char* statespath)//ステータスのロード
{
	int ret;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,", &HP, &HPMAX, &MP, &MPMAX, &STR, &Lv, &EXP, &EXPMAX) != EOF) {};
	fclose(fp);
	return TRUE;
}

BOOL PlayerStates::SAVE_STATES(const char* statespath)//ステータスのセーブ
{
	FILE* fp = fopen(statespath, "w");
	fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,", HP, HPMAX, MP, MPMAX, STR, Lv, EXP, EXPMAX);
	fclose(fp);
	return TRUE;
}