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

	//���x���A�b�v��statesUp�̊�b�l
	int uHP = 8;
	int uMP = 2;
	int uSTR = 5;
	int uAVI = 6;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT,DF,MDF, AGI, Lv, EXP,EXPMAX;
	BOOL isRun=FALSE;

	char Name[10] = { "�C���n\0" };
	
	BOOL INPUT_STATES(const char*);//�X�e�[�^�X�̃��[�h

	BOOL SAVE_STATES(const char*);//�X�e�[�^�X�̃Z�[�u

	void CHANGE_SWORD(int,int);//����̐؂�ւ�

	void RUN_AWAY(int);

	void LEVELUP()//���x���A�b�v�֐��i�r���j
	{
		SRand(1);
		int randam = Lv / 10 + 2;
		HP += uHP * Lv / 10 + GetRand(randam);
		return;
	}

	int DAMAGE_CALC(int, int&);
};

BOOL PlayerStates::INPUT_STATES(const char* statespath)//�X�e�[�^�X�̃��[�h
{
	int ret;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		&HP, &HPMAX, &MP, &MPMAX, &STR,&DF,&MDF, &AGI,&Lv, &EXP, &EXPMAX) != EOF) {};
	fclose(fp);
	return TRUE;
}

BOOL PlayerStates::SAVE_STATES(const char* statespath)//�X�e�[�^�X�̃Z�[�u
{
	FILE* fp = fopen(statespath, "w");
	fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		HP, HPMAX, MP, MPMAX, STR, DF, MDF, AGI, Lv, EXP, EXPMAX);
	fclose(fp);
	return TRUE;
}

int PlayerStates::DAMAGE_CALC(int bougyo, int& HP)//�_���[�W�v�Z��
{
	int damage = int((this->AT*AT) / (this->AT + bougyo));
	HP -= damage;
	if (HP <= 0)//HP���O�ȉ��̎�
	{
		HP = 0;
		return 1;
	}
	return 0;//����ȊO�̎�
}

void PlayerStates::CHANGE_SWORD(int oldsword, int newsword)//����̐؂�ւ�
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