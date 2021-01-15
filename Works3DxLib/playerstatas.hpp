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

class Skill_Management//�X�L�����Ǘ�����֐�
{
public:
	//��U�X�L�����C���v�b�g����o�t�ϐ�
	char bufName[10][15] = { "\0" };
	float bufhosei[10] = { 0 };
	float bufcri[10] = { 0 };
	int bufmp[10] = { 0 };
	int flg[10] = { 0 };
	//�X�L����\���ł���悤�ɂ�����ԕϐ�
	char Name[10][15] = { "\0" };
	float hosei[10] = { 0 };
	float cri[10] = { 0 };
	int mp[10] = { 0 };

	BOOL SAVE_SKILL(const char*);//�X�L���̃Z�[�u
	BOOL INPUT_SKILL(const char*);//�X�L���̃��[�h
	BOOL REGISTER_SKILL();//�X�L����o�^����
};

BOOL Skill_Management::INPUT_SKILL(const char* skillpath)//�X�L���̃��[�h
{
	int ret, n = 0;
	FILE* fp = fopen(skillpath, "r");
	while (ret = fscanf(fp, "%s,%f,%f,%d,%d,",
		&bufName[n], &bufhosei[n], &bufcri[n], &bufmp[n], &flg[n]) != EOF) {
		n++;
	};
	if (ret == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), skillpath, "�X�L���f�[�^�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
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
	int HP, HPMAX, MP, MPMAX, STR, AT, MSTR, MAT, DF, MDF, AGI, Lv, EXP, EXPMAX;//�X�e�[�^�X
	int bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
	int damage = 0;
	BOOL isRun = FALSE;
	int bufAT, bufDF, bufMDF, bufAGI;//�o�t���݂̃X�e�[�^�X
	int OldbufAT, OldbufDF, OldbufMDF, OldbufAGI;
	float DamageHosei = 1.00;
	//float HPver = ((float)HP / (float)HPMAX) * 100;//HP�o�[�̒���
	int critical = 10;
	int cricnt = 0;
	BOOL criflg = FALSE;
	//�Z
	char skillname[7] = { "�����p" };

	//�r���@�������@�_�����@�����@�ψꑫ�@�J�����I�@�ϕԂ�
	//�}���ɓ�����m��������
	char skillname2[10] = { "�����p" };
	//�u�΁@�ω΁@�������@�s�m�΁@���`:�Ӊ΍��X�@�ωΕ��
	float skillhosei2 = 1.2;
	//�m���ő�����₯�ǂɂ���
	char skillname3[10] = { "���p" };
	//�ϕ\
	char skillname4[10] = { "���@" };
	//
	float skillhosei3 = 1.1;
	//�񑮐��̂ɘA��
	//�������


	//�Z�p�̊֐�
	Skill_Management IAI;

	BOOL SKILL_IAI_MUTUKI(int, int&, int);

	char Name[30] = { "\0" };

	BOOL INPUT_STATES(const char*);//�X�e�[�^�X�̃��[�h

	BOOL SAVE_STATES(const char*);//�X�e�[�^�X�̃Z�[�u

	void CHANGE_SWORD(int, int);//����̐؂�ւ�

	void RUN_AWAY(int);

	BOOL LEVELUP();//���x���A�b�v�֐�
	VOID LvUPBUF_NEW();//���x���A�b�v�̏㏸�l�̕ۑ��ϐ���������
	BOOL DMcalcflg = TRUE;
	int DAMAGE_CALC(int, int&);//�_���[�W�v�Z�̊֐�(����̖h���,�����HP)
	int SKILL_IAI_CALC(int, int&,int);
	int KIKON_HOTAL_CALC(int, int&);
	VOID CRI_MESSAGE(int&, int,int&);//�N���e�B�J���̕\������(�ύX����ϐ�,�ύX����V�[��)
};

BOOL Skill_Management::REGISTER_SKILL()//�K���ς݂̋Z��o�^����֐�
{
	int N = 0;
	for (int n = 0; n < 10; n++)
	{
		if (flg[n] == 1)//�Z�̏K���t���O��TRUE�̎�
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
	if (HP <= 0)//HP���O�ȉ��̎�
	{
		HP = 0;
		return 1;
	}
	return 0;//����ȊO�̎�
}

VOID PlayerStates::CRI_MESSAGE(int& sceneflg, int scene,int& Message)
{
	if (this->criflg == TRUE) {//�N���e�B�J��������
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

VOID PlayerStates::LvUPBUF_NEW()//���x���A�b�v�̏㏸�l��������
{
	bHPMAX = 0, bMPMAX = 0, bSTR = 0, bMSTR = 0, bDF = 0, bMDF = 0, bAGI = 0, bLv = 0;
}

BOOL PlayerStates::LEVELUP()
{
		if (EXPMAX > EXP) { return FALSE; }
		while (EXPMAX < EXP)
		{
				int randam = 2;
				//�㏸�ʂ�ۑ�����
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
		//�㏸�ʂ𑝕�
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