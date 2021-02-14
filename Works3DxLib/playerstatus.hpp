#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "BATTLEEFFECT.hpp"
#define PLAYER_STATES TEXT(".\\STATES\\PlayerStates.csv")

#define PLAYER_SAVE1_PSTATUS TEXT(".\\SAVEDATA\\SAVESLOT01\\PlayerStates.csv")
#define PLAYER_SAVE1_PLACE TEXT(".\\SAVEDATA\\SAVESLOT01\\PlayerPlace.csv")
#define PLAYER_SAVE1_PLAYTIME TEXT(".\\SAVEDATA\\SAVESLOT01\\PlayerPlayTime.csv")

#define PLAYER_SAVE2_PSTATUS TEXT(".\\SAVEDATA\\SAVESLOT02\\PlayerStates.csv")
#define PLAYER_SAVE2_PLACE TEXT(".\\SAVEDATA\\SAVESLOT02\\PlayerPlace.csv")
#define PLAYER_SAVE2_PLAYTIME TEXT(".\\SAVEDATA\\SAVESLOT02\\PlayerPlayTime.csv")

#define PLAYER_SAVE3_PSTATUS TEXT(".\\SAVEDATA\\SAVESLOT03\\PlayerStates.csv")
#define PLAYER_SAVE3_PLACE TEXT(".\\SAVEDATA\\SAVESLOT03\\PlayerPlace.csv")
#define PLAYER_SAVE3_PLAYTIME TEXT(".\\SAVEDATA\\SAVESLOT03\\PlayerPlayTime.csv")

#define PLAYER_SKILL_IAI_DATA TEXT(".\\SKILLS\\IAIskill.txt")
#define PLAYER_SKILL_KIKON_DATA TEXT(".\\SKILLS\\KIKONskill.txt")
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
	char bufexpl[10][100] = { "\0" };
	float bufhosei[10] = { 0 };
	float bufcri[10] = { 0 };
	int bufmp[10] = { 0 };
	int flg[10] = { 0 };
	//�X�L����\���ł���悤�ɂ�����ԕϐ�
	char Name[10][15] = { "\0" };
	char expl[10][100] = { "\0" };
	float hosei[10] = { 0 };
	float cri[10] = { 0 };
	int mp[10] = { 0 };

	int Viewtag = 0;

	int isView = 0;
	BOOL SAVE_SKILL(const char*);//�X�L���̃Z�[�u
	BOOL INPUT_SKILL(const char*);//�X�L���̃��[�h
	BOOL REGISTER_SKILL();//�X�L����o�^����
};

BOOL Skill_Management::INPUT_SKILL(const char* skillpath)//�X�L���̃��[�h
{
	int ret, n = 0;
	FILE* fp = fopen(skillpath, "r");
	while (ret = fscanf(fp, "%s%f%f%d%d%s",
		bufName[n], &bufhosei[n], &bufcri[n], &bufmp[n], &flg[n],bufexpl[n]) != EOF) {
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

BOOL Skill_Management::REGISTER_SKILL()//�K���ς݂̋Z��o�^����֐�
{
	int N = 0;
	for (int n = 0; n < 10; n++)
	{
		if (flg[n] == 1)//�Z�̏K���t���O��TRUE�̎�
		{
			strcpy(Name[N], bufName[n]);
			strcpy(expl[N], bufexpl[n]);
			hosei[N] = bufhosei[n];
			cri[N] = bufcri[n];
			mp[N] = bufmp[n];
			N++;
		}
	}
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
	Skill_Management IAI, KIKON, KEN,MAGIC;

	BOOL SKILL_IAI_MUTUKI(int, int&, int);

	char Name[30] = { "\0" };

	BOOL INPUT_STATES(const char*);//�X�e�[�^�X�̃��[�h
	BOOL INPUT_PLAYTIME(const char*);//�v���C���Ԃ̃��[�h
	BOOL INPUT_PLAYER_PLACE(int&,int&,const char*);

	BOOL SAVE_STATES(const char*);//�X�e�[�^�X�̃Z�[�u
	BOOL SAVE_PLAYTIME(const char*,int);//�v���C���Ԃ̃Z�[�u
	BOOL SAVE_PLAYER_PLACE(int,int,const char*);//�v���C���[�̏ꏊ��ۑ�

	void CHANGE_SWORD(int, int);//����̐؂�ւ�

	void RUN_AWAY(int);

	BOOL LEVELUP();//���x���A�b�v�֐�
	VOID LvUPBUF_NEW();//���x���A�b�v�̏㏸�l�̕ۑ��ϐ���������
	BOOL DMcalcflg = TRUE;
	int DAMAGE_CALC(int, int&);//�_���[�W�v�Z�̊֐�(����̖h���,�����HP)
	int SKILL_IAI_CALC(int, int&,int);
	int SKILL_KIKON_CALC(int, int&,int);
	VOID CRI_MESSAGE(int&, int,int&);//�N���e�B�J���̕\������(�ύX����ϐ�,�ύX����V�[��)
	VOID PLAYTIME_CALC_F();
	//�v���C���Ԃ̍ŏ��̒l��o�^����֐�
	VOID PLAYTIME_CALC_E(int);
	VOID PLAYTIME_STATE();
	int bhour[3], bminutes[3], bsecond[3];
	//�v���C���Ԃ̍Ō�̒l��o�^���A���v���C���Ԃ��v�Z����֐�
	int PlayTimeF=0, PlayTimeE=0,FullPlayTime=0; BOOL CountPlayTimeflg = TRUE;

	//�Z�[�u�f�[�^�\���p�Ƀf�[�^���ꎞ�I�Ƀ��[�h����֐�
	BOOL bufLOADINGDATA(int,const char*,const char*);
	int bufLHP[3], bufLHPMAX[3], bufLMP[3], bufLMPMAX[3], bufLSTR[3], bufLMSTR[3], bufLDF[3],
		bufLMDF[3], bufLAGI[3], bufLLv[3], bufLEXP[3], bufLEXPMAX[3];
	int bufFullTime[3];
	char bufLName[3][30];

	int USE_ITEM(int, int,int,int,int&,int&,int&);
	VOID BUF_CALC(int,int&);
};

int PlayerStates::USE_ITEM(int HPheal, int MPheal,int goodhosei,int badhosei,
	int& bufSTR, int& bufDEF,int&Itemhave)
{
	if ((HP == HPMAX && MP == MPMAX)||Itemhave<=0)
	{
		return -1;
	}
	else {
		HP += HPheal;//HP���񕜂���
		if (HP > HPMAX)
		{
			HP = HPMAX;
		}
		MP += MPheal;//MP���񕜂���
		if (MP > MPMAX)
		{
			MP = MPMAX;
		}
		BUF_CALC(goodhosei,bufSTR);
		Itemhave--;
		return 0;
	}
}

VOID PlayerStates::BUF_CALC(int bufhosei,int& bufSTATUS)
{
	if (bufhosei <= 0)//�o�t���ʂ��Ȃ����߂�
	{
		return;
	}
	float bufStatus = bufSTATUS * bufhosei;
	if (bufStatus < 1)//�o�t���ʂ�1��菬������1�𑫂�
	{
		bufSTATUS += 1;
	}
	else
	{
		bufSTATUS += int(bufStatus);
	}
	return;
}

VOID PlayerStates::PLAYTIME_STATE()
{
	for (int i = 0; i < 3; i++)
	{
		float buf = bufFullTime[i];
		bhour[i] = int(buf / (1000.0 * 60.0 * 60.0));
		if (bhour[i] == 0) {}
		else
		{
			buf = buf - (bhour[i] * 60.0 * 60.0 * 1000.0);
		}
		bminutes[i] = int(buf / (1000.0 * 60.0));
		if(bminutes[i]==0){}
		else
		{
			buf = buf - (bminutes[i] * 60.0 * 1000.0);
		}
		bsecond[i] = int(buf / 1000.0);
	}
	return;
}

//�Z�[�u�f�[�^�\���p�Ƀf�[�^���ꎞ�I�Ƀ��[�h����֐�
BOOL PlayerStates::bufLOADINGDATA(int SaveNum,const char* statespath,const char* timepath)
{
	int ret, ret2;
	FILE* fp = fopen(statespath, "r"), *fp2 = fopen(timepath, "r");
	//�o�b�t�@�ɉ��̃Z�[�u�f�[�^��ۑ�
	while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,",
		&bufLHP[SaveNum], &bufLHPMAX[SaveNum], &bufLMP[SaveNum], &bufLMPMAX[SaveNum], &bufLSTR[SaveNum],
		&bufLMSTR[SaveNum], &bufLDF[SaveNum],&bufLMDF[SaveNum], &bufLAGI[SaveNum],
		&bufLLv[SaveNum], &bufLEXP[SaveNum], &bufLEXPMAX[SaveNum], &bufLName[SaveNum]) != EOF) {};
	while (ret2 = fscanf(fp2, "%d,", &bufFullTime[SaveNum]) != EOF) {};
	if (ret == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), statespath, "�o�t�Z�[�u�f�[�^�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	fclose(fp), fclose(fp2);
	return TRUE;
}

VOID PlayerStates::PLAYTIME_CALC_F() {
	PlayTimeF = GetNowCount();
	CountPlayTimeflg = FALSE;
	return;
}

VOID PlayerStates::PLAYTIME_CALC_E(int saveslot) {
	FullPlayTime= bufFullTime[saveslot]+GetNowCount() - PlayTimeF;
	CountPlayTimeflg = TRUE;
	return;
}

BOOL PlayerStates::SAVE_PLAYTIME(const char* timepath, int saveslot)//�v���C���Ԃ��L�^����
{
	PLAYTIME_CALC_E(saveslot);
	FILE* fp = fopen(timepath, "w");
	fprintf(fp, "%d",FullPlayTime);
	fclose(fp);
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

BOOL PlayerStates::INPUT_PLAYER_PLACE(int& playerX, int& playerY, const char* placepath)
{
	int ret;
	FILE* fp = fopen(placepath, "r");
	while (ret = fscanf(fp, "%d,%d,", &playerX, &playerY)!=EOF) {};
	if (ret == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), placepath, "�Z�[�u�f�[�^�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL PlayerStates::SAVE_PLAYER_PLACE(int playerX,int playerY,const char* placepath)
{																					//�ꏊ�̃Z�[�u
	FILE* fp = fopen(placepath, "w");
	fprintf(fp, "%d,%d,",playerX,playerY);
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

BOOL PlayerStates::SKILL_IAI_CALC(int bougyo,int& hp,int skillnum)//�����Z�̃_���[�W�v�Z��
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

BOOL PlayerStates::SKILL_KIKON_CALC(int enMDF, int& hp, int skillnum)
{
	int cri = GetRand(criRan);
	damage = int(((this->MAT * MAT) / (this->MAT + enMDF)) * KIKON.hosei[skillnum]);
	if (cri < this->critical)//�N���e�B�J�����͒ʏ�
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
		while (EXPMAX <= EXP)
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
		HP = HPMAX;//HP���񕜂���
		return TRUE;
}