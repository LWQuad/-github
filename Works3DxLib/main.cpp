#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include <iostream>
#include <string>
using namespace std;
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

#define PLAYER_STATES TEXT(".\\STATES\\PlayerStates.csv")

#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_SCENE	//�Q�[���V�[���̗�
{
	GAME_START_SCENE,
	GAME_PLAY_SCENE,
	GAME_BATTLE_SCENE,
	GAME_EVENT_SCENE,
	GAME_END_SCENE
};

class LOAD_SINGLE_IMAGE //�摜�ꖇ��ǂݍ��ރN���X
{
public:
	char path[PATH_MAX];		//�p�X
	char pathname[PATH_MAX];
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
	BOOL IsDraw;				//�\���̉�

	BOOL LOADING_IMAGE(const char* pathname)
	{
		strcpy(this->path, pathname);
		this->handle = LoadGraph(this->path);			//�ǂݍ���
		if (this->handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), pathname, "�摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
			return FALSE;
		}
		GetGraphSize(this->handle, &this->width, &this->height);	//�摜�̕��ƍ������擾
		this->x = GAME_WIDTH / 2 - this->width / 2;		//���E��������
		this->y = GAME_HEIGHT / 2 - this->height / 2;		//�㉺��������
		return TRUE;
	}
};

class CREATE_FONTHANDLE
{
public:
	char path[PATH_MAX];		//�p�X
	char name[NAME_MAX];		//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v

	BOOL CREATE_FONT(int fontsize,const char* fontpath,const char* fontname)
		//�t�H���g�T�C�Y�@�t�H���g�̃p�X�@�t�H���g�̖��O�������Ɏg�p
	{
		strcpy_s(this->path, sizeof(this->path), fontpath);	//�p�X���R�s�[
		strcpy_s(this->name, sizeof(this->name), fontname);	//�t�H���g�����R�s�[
		this->handle = -1;								//�n���h����������
		this->size = fontsize;								//�T�C�Y�������ɂ���
		this->bold = 1;								//����1
		this->type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

		//�t�H���g�n���h���쐬
		this->handle = CreateFontToHandle(this->name, this->size, this->bold, this->type);
		//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
		if (this->handle == -1) { MessageBox(GetMainWindowHandle(), fontpath, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }
		return TRUE;
	}

	~CREATE_FONTHANDLE()//�t�H���g�n���h�����폜
	{
		DeleteFontToHandle(this->handle);
	}
};

class MUSIC
{
public:

	char path[PATH_MAX];		//�p�X
	int handle;

	BOOL LOAD_MUSIC(const char* musicpath)
	{
		strcpy_s(path,musicpath);				//�p�X�̐ݒ�
		handle = LoadSoundMem(path);			//�ǂݍ���
		if (handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), musicpath, "���y�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
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

	//statesUp�̊�b�l
	int uHP = 8;
	int uMP = 2;
	int uSTR = 5;
	int uAVI = 6;
public:
	int HP,MP,STR,AT,AVG,Lv,EXP;
	int EXPMAX;
	void INPUT_STATES()//�t�@�C������X�e�[�^�X�̃��[�h
	{
		int ret;
		FILE* fp = fopen(PLAYER_STATES, "r");
		while (ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,", &HP, &MP, &STR, &Lv, &EXP, &EXPMAX) != EOF) {};
		fclose(fp);
		return;
	}

	void SAVE_STATES()//�X�e�[�^�X�̃Z�[�u
	{
		int ret;
		FILE* fp = fopen(PLAYER_STATES, "w");
		fprintf(fp, "%d,%d,%d,%d,%d,%d,", HP, MP, STR, Lv, EXP, EXPMAX);
		fclose(fp);
		return;
	}

	void LEVELUP()//���x���A�b�v�֐��i�r���j
	{
		SRand(1);
		int randam = Lv / 10+2;
		HP += uHP*Lv/10+GetRand(randam);
		return;
	}
};

PlayerStates Pstates;

VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

VOID MY_BATTLE(VOID);			//�o�g�����
VOID MY_BATTLE_PROC(VOID);		//�o�g����ʂ̏���
VOID MY_BATTLE_DRAW(VOID);		//�o�g����ʂ̕`��

VOID MY_EVENT(VOID);			//�C�x���g���
VOID MY_EVENT_PROC(VOID);		//�C�x���g��ʂ̏���
VOID MY_EVENT_DRAW(VOID);		//�C�x���g��ʂ̕`��

LOAD_SINGLE_IMAGE title;
LOAD_SINGLE_IMAGE player;
LOAD_SINGLE_IMAGE enemy;
CREATE_FONTHANDLE tanu20;
int GameScene;//�Q�[���V�[�����Ǘ�����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
/*	SetWindowIconID(IDI_ICON1);*/							//�A�C�R���t�@�C����Ǎ�

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	if (title.LOADING_IMAGE(IMAGE_TITLE) == -1) { return -1; }
	if (player.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return -1; }
	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

	GameScene = GAME_BATTLE_SCENE;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�X�^�[�g�����܂��Ă��Ȃ����
	//if (startPt.x == -1 && startPt.y == -1)
	//{
	//	//�G���[���b�Z�[�W�\��
	//	MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	//}

	////�S�[�������܂��Ă��Ȃ����
	//if (GoalRect.left == -1)
	//{
	//	//�G���[���b�Z�[�W�\��
	//	MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	//}
	tanu20.CREATE_FONT(20,FONT_TANU_PATH,FONT_TANU_NAME);
	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		//MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		//MY_MOUSE_UPDATE();						//�}�E�X�̏�Ԃ��擾

		//MY_FPS_UPDATE();	//FPS�̏���[�X�V]

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
			case GAME_START_SCENE:
				MY_START();	//�X�^�[�g���
				break;
			case GAME_PLAY_SCENE:
				MY_PLAY();	//�v���C���
				break;
			case GAME_BATTLE_SCENE:
				MY_BATTLE(); //�o�g�����
				break;
			case GAME_EVENT_SCENE:
				MY_EVENT(); //�C�x���g���
				break;
			case GAME_END_SCENE:
				MY_END(); //�G���h���
				break;
		}
		//DrawGraph(title.x, title.y, title.handle, TRUE);
		//MY_FPS_DRAW();		//FPS�̏���[�`��]
		Pstates.INPUT_STATES();
		Pstates.SAVE_STATES();

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		//MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	int DxLib_End();
	return 0;
}
	////�t�H���g�n���h����j��
	//MY_FONT_DELETE();

	////�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	//MY_FONT_UNINSTALL_ONCE();

	////�摜�n���h����j��
	//MY_DELETE_IMAGE();

	////���y�n���h����j��
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

