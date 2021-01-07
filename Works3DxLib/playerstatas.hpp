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
	int uMSTR = 5;
	int uAGI = 6;
	int uDF = 5;
	int uMDF = 5;
	//int uEXP=50;
	int criRan = 100;
public:
	int HP, HPMAX, MP, MPMAX, STR, AT,MSTR,MAT,DF,MDF, AGI, Lv, EXP,EXPMAX;//�X�e�[�^�X
	int bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
	int damage = 0;
	BOOL isRun=FALSE;
	int bufAT, bufDF, bufMDF, bufAGI;//�o�t���݂̃X�e�[�^�X
	int OldbufAT, OldbufDF, OldbufMDF, OldbufAGI;
	float DamageHosei = 1.00;
	//float HPver = ((float)HP / (float)HPMAX) * 100;//HP�o�[�̒���
	int critical = 100;
	BOOL criflg = FALSE;
	//�Z
	char skillname[7] = { "�����p" };
	float skillhosei = 1.4;
	//�}���ɓ�����m��������
	char skillname2[10] = { "�����p" };
	float skillhosei2 = 1.2;
	//�m���ő�����₯�ǂɂ���
	char skillname3[10] = { "���p" };

	char skillname4[10] = { "���@" };
	float skillhosei3 = 1.1;
	//�񑮐��̂ɘA��
	//�������

	//�Z�p�̊֐�
	BOOL SKILL_IAI_MUTUKI(int,int&,int);

	char Name[30] = { "\0" };
	
	BOOL INPUT_STATES(const char*);//�X�e�[�^�X�̃��[�h

	BOOL SAVE_STATES(const char*);//�X�e�[�^�X�̃Z�[�u

	void CHANGE_SWORD(int,int);//����̐؂�ւ�

	void RUN_AWAY(int);

	BOOL LEVELUP()//���x���A�b�v�֐��i�r���j
	{
		if (EXP >= EXPMAX)
		{
			while (1)
			{
				if (EXPMAX - EXP >= 0)
				{
					SRand(1);
					int randam = Lv / 10 + 2;
					//�㏸�ʂ�ۑ�����
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
			//�㏸�ʂ𑝕�
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

	int DAMAGE_CALC(int, int&);//�_���[�W�v�Z�̊֐�(����̖h���,�����HP)
	int IAI_KITUNEISSOKU_CALC(int, int&);
	int KIKON_HOTAL_CALC(int, int&);
};

BOOL PlayerStates::INPUT_STATES(const char* statespath)//�X�e�[�^�X�̃��[�h
{
	int ret;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
		&HP, &HPMAX, &MP, &MPMAX, &STR,&MSTR,&DF,&MDF, &AGI,&Lv, &EXP, &EXPMAX,&Name) != EOF) {};
	if (ret == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), statespath, "�Z�[�u�f�[�^�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	fclose(fp);
	return TRUE;
}

BOOL PlayerStates::SAVE_STATES(const char* statespath)//�X�e�[�^�X�̃Z�[�u
{
	FILE* fp = fopen(statespath, "w");
	fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
		HP, HPMAX, MP, MPMAX, STR, MSTR,DF, MDF, AGI, Lv, EXP, EXPMAX,Name);
	fclose(fp);
	return TRUE;
}

int PlayerStates::DAMAGE_CALC(int bougyo, int& HP)//�_���[�W�v�Z��
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

BOOL PlayerStates::SKILL_IAI_MUTUKI(int bougyo,int& hp,int bufAT)
{
	this->DamageHosei = 1.4;
	int damage = int(((bufAT*bufAT) / (this->AT + bougyo)) * DamageHosei);
	this->DamageHosei = 1.0;
	HP -= damage;
	if (HP <= 0)//HP���O�ȉ��̎�
	{
		HP = 0;
		return 1;
	}
	return 0;//����ȊO�̎�
}