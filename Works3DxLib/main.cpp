#include "DxLib.h"
#include "windowsystem.h"
#include "image.hpp"
#include "font.hpp"
#include "map.hpp"
#include "player.hpp"
#include "hitbox.hpp"
#include "battleUI.hpp"
#include "enemystatas.hpp"
#include "playerstatas.hpp"
#include "Battlesystem.hpp"
#include "BATTLEEFFECT.hpp"
#include "Item.hpp"
#include "music.hpp"
#include "StatesUI.hpp"
#include "startUI.hpp"
#include "event.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MOVE_MAP_UP 5
#define MOVE_MAP_LEFT 5
#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_SCENE	//�Q�[���V�[���̗�
{
	GAME_START_SCENE,
	GAME_PLAY_SCENE,
	GAME_BATTLE_SCENE,
	GAME_EVENT_SCENE,
	GAME_END_SCENE,
	GAME_STATES_SCENE
};

enum BATTLE_MESSAGE
{
	ENCOUNT,
	SELECT_NORMAL_AT,
	NORMAL_AT,
	SKILL,
	GUARD,
	SELECT_ITEM,
	RUN,
	CRITICAL,
	DEFEAT_EN,
	GET_EXP,
	GIVE_DAMAGE,
	Levelup
};

class HPbar
{
	int HPwidth = 100;
};

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

VOID MY_STATES(VOID);			//�C�x���g���
VOID MY_STATES_PROC(VOID);		//�C�x���g��ʂ̏���
VOID MY_STATES_DRAW(VOID);		//�C�x���g��ʂ̕`��

VOID BATTLE_PROC_NEW(VOID);		//�o�g���V�[��������������֐�
BOOL LOADING_FULL_IMAGE(VOID);	//�摜�S�Ă����[�h����֐�
VOID LOADING_FULL_MAP(VOID);	//�}�b�v��ǂݍ��ފ֐�
VOID CREATE_FULL_FONT(VOID);	//�t�H���g���쐬����֐�
BOOL LOADING_FULL_MUSIC(VOID);	//���y��ǂݍ��ފ֐�
VOID INPUTBTLSTATES_BUF(VOID);	//1�퓬�p�ɃX�e�[�^�X��ޔ�������֐�
VOID PLAY_CARSOL_SOUND(VOID);	//�J�[�\������炷(���ԒZ�k�p)
VOID PLAY_ENTER_SOUND(int);	//���艹��炷(���ԒZ�k�p)(�Đ��^�C�v��ݒ�)
VOID DRAW_MESSAGE(int);

PlayerStates Pstates;
EnemyStates Estates;
LOAD_SINGLE_IMAGE title;
LOAD_SINGLE_IMAGE titlelogo;
LOAD_SINGLE_IMAGE Bplayer;
LOAD_SINGLE_IMAGE enemy;
LOAD_SINGLE_IMAGE btbk;
LOAD_SINGLE_IMAGE UIback;
BATTLE_EFFECT BEffectNormal;
CREATE_FONTHANDLE tanu20;
CREATE_FONTHANDLE tanu30;
CREATE_FONTHANDLE tanu30n;
MAP_DIV divmap;//�}�b�v�`�b�v�����p�N���X
MAPINPUT MAPUND;//���̃}�b�v
MAPINPUT MAPMID;//���̃}�b�v
MAPINPUT MAPON;//��̃}�b�v
MAP_HITBOX MAPHIT;//�����蔻��̃}�b�v
MAP_ENEMY MAPEN;//�G�̏o���}�b�v
//ENEMY Senemy;
CHARA player;
BATTLE_SYSTEM Bsys;
BATTLE_UI UI;
STATES_UI S_UI;
START_UI F_UI;
DEFAULT_COLOR C;
EVENT eventS;
ITEM item;
MUSIC PlayBGM;
MUSIC BTBGM1;
MUSIC BTSEnor;
MUSIC BTSEENnor;
MUSIC BTcar, BTenter;
MUSIC OverBGM;
MUSIC TitleBGM;

int GameScene;//�Q�[���V�[�����Ǘ�����
int Message;//���b�Z�[�W���Ǘ�
//�U�����x�̔�������邩�ۂ��̊֐�
int Battleflag = 0;
//0�̎��������U���@�P�̎��G���U��
int Playerflag = 0;
//�s����̏���
int Playendflag = 0;
//�G�̍s������
int Enemyflag = 0;
//�X�L���̍s������
int skillflag = 0;

BOOL Levelupflag;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
/*	SetWindowIconID(IDI_ICON1);*/							//�A�C�R���t�@�C����Ǎ�

	

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	if (LOADING_FULL_IMAGE() == FALSE) { return -1; }//�S�Ẳ摜��ǂݍ���
	if (LOADING_FULL_MUSIC() == FALSE) { return -1; }//�S�Ẳ��y��ǂݍ���
	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��
	LOADING_FULL_MAP();				//�}�b�v��ǂݍ��ފ֐�
	CREATE_FULL_FONT();				//�t�H���g���쐬����֐�
	/*item.INPUTSTATES_SYUDOU(20, "�₭����", 0);*/

	GameScene = GAME_START_SCENE;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	eventS.INPUTTXT(EVENT_TXT);
	//start�ʒu�̐ݒ�
	player.image.x = divmap.width*10; player.image.y =divmap.height*11 ;
	player.Nowhandle = player.image.Divhandle[0];
	UI.UIx[0] = UI.SpotUIx;
	Pstates.INPUT_STATES(PLAYER_STATES);

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��
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
			case GAME_STATES_SCENE:
				MY_STATES(); //�G���h���
				break;
		}
		//MY_FPS_DRAW();		//FPS�̏���[�`��]
		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��
		//MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	DxLib_End();
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
	F_UI.C_count++;
	F_UI.E_count++;
	if (CheckSoundMem(TitleBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, TitleBGM.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(TitleBGM.handle, DX_PLAYTYPE_LOOP);
	}

	if (CheckHitKey(KEY_INPUT_UP) == TRUE && F_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		if (F_UI.tag <= 0) {
			F_UI.tag = 0;
		}
		else
		{
			F_UI.C_count = 0;
			F_UI.tag -= 1;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && F_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		if (F_UI.tag >=1) {
			F_UI.tag = 1;
		}
		else
		{
			F_UI.C_count = 0;
			F_UI.tag += 1;
		}
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(TitleBGM.handle) != 0)
		{
			StopSoundMem(TitleBGM.handle);
		}
		PLAY_ENTER_SOUND(DX_PLAYTYPE_NORMAL);
		GameScene = GAME_PLAY_SCENE;
	}

	return;
}
VOID MY_START_DRAW()
{
	DrawGraph(title.x, title.y, title.handle, TRUE);
	DrawGraph(titlelogo.x, 150, titlelogo.handle, TRUE);
	int Nsize=GetDrawStringWidthToHandle("�͂��߂���",11,tanu30n.handle);
	DrawFormatStringToHandle(GAME_WIDTH/2-Nsize/2, 400, C.Black, tanu30n.handle, "�͂��߂���");
	int Lsize = GetDrawStringWidthToHandle("�Â�����", 11, tanu30n.handle);
	DrawFormatStringToHandle(GAME_WIDTH / 2 - Lsize / 2, 500, C.Black, tanu30n.handle, "�Â�����");
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
	S_UI.S_count++;
	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE &&S_UI.CHECK_CHENGE_COUNT_STorPLY()==TRUE )//�X�e�[�^�X��ʂɈړ�
	{
		S_UI.S_count = 0;
		GameScene = GAME_STATES_SCENE;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE && S_UI.CHECK_CHENGE_COUNT_STorPLY() == TRUE)//�X�e�[�^�X��ʂɈړ�
	{
		S_UI.S_count = 0;
		GameScene = GAME_EVENT_SCENE;
	}
	//�v���C���[�̓����蔻���ݒ�
	player.coll.left = player.image.x + 5;
	player.coll.top = player.image.y + 5;
	player.coll.right = player.image.x + player.image.width - 5;
	player.coll.bottom = player.image.y + player.image.height - 5;

	//�ړ��O�̃v���C���[�̏ꏊ���擾
	player.OldX = player.image.x;
	player.OldY = player.image.y;
	if (CheckHitKey(KEY_INPUT_UP) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[10];
		player.coll.top -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else{ player.image.y -= 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGM���~�߂�
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;}
		if (MAPON.y[0][0] < 0 && player.image.y < 100)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//�}�b�v��`��
					MAPON.y[tate][yoko] += 5;
					MAPMID.y[tate][yoko] += 5;
					MAPUND.y[tate][yoko] += 5;
					MAPHIT.y[tate][yoko] += 5;
					MAPHIT.Hitmap[tate][yoko].bottom += 5;
					MAPHIT.Hitmap[tate][yoko].top += 5;
					MAPEN.y[tate][yoko] += 5;
					MAPEN.Hitmap[tate][yoko].bottom += 5;
					MAPEN.Hitmap[tate][yoko].top += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		/*player.image.x -= 5;*/
		player.Nowhandle = player.image.Divhandle[4];
		player.coll.left -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else {
			player.image.x -= 5;
		}
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGM���~�߂�
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.x[0][0] < 0 && player.image.x < 150)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//�}�b�v��`��
					MAPON.x[tate][yoko] += 5;
					MAPMID.x[tate][yoko] += 5;
					MAPUND.x[tate][yoko] += 5;
					MAPHIT.x[tate][yoko] += 5;
					MAPHIT.Hitmap[tate][yoko].left += 5;
					MAPHIT.Hitmap[tate][yoko].right += 5;
					MAPEN.x[tate][yoko] += 5;
					MAPEN.Hitmap[tate][yoko].left += 5;
					MAPEN.Hitmap[tate][yoko].right += 5;
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[1];
		player.coll.bottom += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else { player.image.y += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGM���~�߂�
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;
		}
		if (MAPON.y[MAP_TATE_MAX1 - 1][0] > GAME_HEIGHT && player.image.y > 500)
		{
			player.image.y = player.OldY;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//�}�b�v��`��
					MAPON.y[tate][yoko] -= 5;
					MAPMID.y[tate][yoko] -= 5;
					MAPUND.y[tate][yoko] -= 5;
					MAPHIT.y[tate][yoko] -= 5;
					MAPHIT.Hitmap[tate][yoko].bottom -= 5;
					MAPHIT.Hitmap[tate][yoko].top -= 5;
					MAPEN.y[tate][yoko] -= 5;
					MAPEN.Hitmap[tate][yoko].bottom -= 5;
					MAPEN.Hitmap[tate][yoko].top -= 5;
				}
			}
		}

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		player.Nowhandle = player.image.Divhandle[7];
		player.coll.right += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else { player.image.x += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);	//BGM���~�߂�
			}
			Estates.ENEMY_KIND_FLAG();
			INPUTBTLSTATES_BUF();
			UI.BrightR = UI.BrightMAX, UI.BrightG = UI.BrightMAX, UI.BrightB = UI.BrightMAX;
			GameScene = GAME_BATTLE_SCENE;}
		if (MAPON.x[0][MAP_YOKO_MAX1 - 1] > GAME_WIDTH && player.image.x > 650)
		{
			player.image.x = player.OldX;
			for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
				{
					//�}�b�v��`��
					MAPON.x[tate][yoko] -= 5;
					MAPMID.x[tate][yoko] -= 5;
					MAPUND.x[tate][yoko] -= 5;
					MAPHIT.x[tate][yoko] -= 5;
					MAPHIT.Hitmap[tate][yoko].left -= 5;
					MAPHIT.Hitmap[tate][yoko].right -= 5;
					MAPEN.x[tate][yoko] -= 5;
					MAPEN.Hitmap[tate][yoko].left -= 5;
					MAPEN.Hitmap[tate][yoko].right -= 5;
				}
			}
		}
	}
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x > GAME_WIDTH-divmap.width) { player.image.x = GAME_WIDTH - divmap.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y > GAME_HEIGHT - divmap.height) { player.image.y = GAME_HEIGHT - divmap.height; }
	return;
}

VOID MY_PLAY_DRAW()
{
	SetDrawBright(255, 255, 255);
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)//�v���C���[��艺�̃}�b�v�`��
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//�}�b�v��`��
			/*if(MAPUND.isVIEW==TRUE)*/
			DrawGraph(
				MAPUND.x[tate][yoko],
				MAPUND.y[tate][yoko],
				divmap.handle[MAPUND.kind[tate][yoko]],
				TRUE);
			/*if (MAPMID.isVIEW == TRUE)*/
			DrawGraph(
				MAPMID.x[tate][yoko],
				MAPMID.y[tate][yoko],
				divmap.handle[MAPMID.kind[tate][yoko]],
				TRUE);
			
			/*if (MAPON.isVIEW == TRUE)*/

		}
	}
	//if (player.image.IsDraw == TRUE)
	//{
		DrawGraph(player.image.x, player.image.y, player.Nowhandle, TRUE);
/*	}*///�v���C���[�̕`��
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)//�v���C���[����̃}�b�v�`��
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{

			DrawGraph(
				MAPON.x[tate][yoko],
				MAPON.y[tate][yoko],
				divmap.handle[MAPON.kind[tate][yoko]],
				TRUE);
		}
		//for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		//{
		//	DrawGraph(
		//		MAPHIT.x[tate][yoko],
		//		MAPHIT.y[tate][yoko],
		//		divmap.handle[MAPHIT.kind[tate][yoko]],
		//		TRUE);
		//}
		//for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		//{
		//	DrawGraph(
		//		MAPEN.x[tate][yoko],
		//		MAPEN.y[tate][yoko],
		//		divmap.handle[MAPEN.kind[tate][yoko]],
		//		TRUE);
		//}
	}
//	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
//{
//	for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
//	{
//		//�ǂȂ��
//		if (MAPHIT.kind[tate][yoko] == 63)
//		{
//			DrawBox(MAPHIT.Hitmap[tate][yoko].left, MAPHIT.Hitmap[tate][yoko].top,
//				MAPHIT.Hitmap[tate][yoko].right, MAPHIT.Hitmap[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
//		}
//
//	}
//}
//	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
	return;
}

VOID MY_STATES()
{
	MY_STATES_PROC();
	MY_STATES_DRAW();
	return;
}

VOID MY_STATES_PROC()
{
	S_UI.S_count++;
	S_UI.C_count++;
	if ((CheckHitKey(KEY_INPUT_ESCAPE) == TRUE)&&S_UI.CHECK_CHENGE_COUNT_STorPLY()==TRUE)
	{
		S_UI.S_count = 0;
		GameScene = GAME_PLAY_SCENE;
	}
	if ((CheckHitKey(KEY_INPUT_RIGHT) == TRUE)&&S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		S_UI.Ctag += 1;
		S_UI.C_count = 0;
		if (S_UI.Ctag >=4)
		{
			S_UI.Ctag = 4;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE && S_UI.CHECK_CHENGE_COUNT_CATEGORY() == TRUE)
	{
		S_UI.Ctag -= 1;
		S_UI.C_count = 0;
		if (S_UI.Ctag <= 0)
		{
			S_UI.Ctag = 0;
		}
	}
	return;
}
VOID MY_STATES_DRAW()
{
	float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
	float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;
	float c= ((float)Pstates.EXP / (float)Pstates.EXPMAX) * 300;
	int Color = GetColor(255, 255, 255);
	DrawGraph(0, 0, S_UI.back.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(15, 80, S_UI.back2.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	if (S_UI.Ctag == 0)
	{
		DrawGraph(GAME_WIDTH- S_UI.charaimg.width-20, 124-5,
			S_UI.charaimg.handle, TRUE);
		DrawGraph(0, 0, S_UI.UIimg.UIhandle[0], TRUE);
		DrawBox(50 - 2, 50 - 2, 50 + 100 + 2, 80 + 2, GetColor(255, 255, 255), TRUE);
		DrawBox(50, 50, 50 + (int)a, 80, GetColor(0, 255, 0), TRUE);
		DrawFormatStringToHandle(50, 90
			, Color, tanu30n.handle, "Lv %4d", Pstates.Lv);
		DrawFormatStringToHandle(50, 130
			, Color, tanu30n.handle, "HP %d/%d", Pstates.HP, Pstates.HPMAX);
		DrawFormatStringToHandle(50, 170
			, Color, tanu30n.handle, "MP %d/%d", Pstates.MP, Pstates.MPMAX);
		DrawFormatStringToHandle(50, 210
			, Color, tanu30n.handle, "�����U���� %d(+%d)", Pstates.AT, Pstates.STR);
		DrawFormatStringToHandle(50, 250
			, Color, tanu30n.handle, "�����h��� %d", Pstates.DF);
		DrawFormatStringToHandle(50, 290
			, Color, tanu30n.handle, "���@�h��� %d", Pstates.MDF);
		DrawFormatStringToHandle(50, 330
			, Color, tanu30n.handle, "���΂₳ %d", Pstates.AGI);
		DrawFormatStringToHandle(50, 370
			, Color, tanu30n.handle, "���̃��x���܂� %dExp", Pstates.EXPMAX - Pstates.EXP);
		DrawBox(50 - 2, 405 - 2, 50 + 300 + 2, 410 + 2, GetColor(255, 255, 255), TRUE);
		DrawBox(50, 405, 50 + (int)c, 410, GetColor(0, 255, 0), TRUE);
	}
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
	eventS.count++;
	if (eventS.count > eventS.countMax)
	{
		if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
		{
			eventS.strLnum+=3;
			eventS.count = 0;
		}
	}
	return;
}
VOID MY_EVENT_DRAW()
{
	DrawGraph(0,GAME_HEIGHT-190, eventS.txtUI.handle, TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 120, GetColor(255, 255, 255),
		tanu30.handle,eventS.str[eventS.strLnum],  TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 90, GetColor(255, 255, 255),
		tanu30.handle, eventS.str[eventS.strLnum+1], TRUE);
	DrawFormatStringToHandle(50, GAME_HEIGHT - 60, GetColor(255, 255, 255),
		tanu30.handle, eventS.str[eventS.strLnum+2], TRUE);
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
	if (CheckSoundMem(BTBGM1.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, BTBGM1.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BTBGM1.handle, DX_PLAYTYPE_LOOP);
	}
	Pstates.AT = Pstates.STR;
	UI.CHANGE_COUNT();

	if (UI.Mssgcount > UI.MssgcntMx)
	{
		UI.EncntUIisView = FALSE;
	}
	if (UI.EncntUIisView == TRUE)
	{
		UI.Mssgcount++;
	}
	else
	{
		switch (Battleflag)
		{
		case 0://�v���C���[�̍s��
			switch (Playerflag)
			{
			case 0://�s���I���̏���
				if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//����������Ƃ�
				{
					PLAY_CARSOL_SOUND();
					UI.count = 0;
					UI.UIx[UI.UItag] = UI.NonSpotUIx;
					UI.UItag -= 1;
					if (UI.UItag < 0) { UI.UItag = 4; }
					UI.UIx[UI.UItag] = UI.SpotUIx;
				}
				if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//�����������Ƃ�
				{
					PLAY_CARSOL_SOUND();
					UI.count = 0;
					UI.UIx[UI.UItag] = UI.NonSpotUIx;
					UI.UItag += 1;
					if (UI.UItag > 4) { UI.UItag = 0; }
					UI.UIx[UI.UItag] = UI.SpotUIx;
				}
				if (UI.UItag == 0) { Message = SELECT_NORMAL_AT; }
				if (UI.UItag == 1) { Message = SKILL; }
				if (UI.UItag == 2) { Message = GUARD; }
				if (UI.UItag == 3) { Message = SELECT_ITEM; }
				if (UI.UItag == 4) { Message = RUN; }
				if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)//�G���^�[���������Ƃ�
				{
					PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
					Playerflag = 1;
				}
				break;
			case 1://�s���I�����̓���
				switch (UI.UItag)
				{
				case 0://�ʏ�U��
					switch(BEffectNormal.effectflg)
					{ 
					case 0://�G�t�F�N�g�`��ӏ�
					Message = NORMAL_AT;
					BEffectNormal.isView = TRUE;//�o�g���G�t�F�N�g��`�悷��
					if (CheckSoundMem(BTSEnor.handle) == 0)
					{
						//BGM�̉��ʂ�������
						ChangeVolumeSoundMem(255 * 50 / 100, BTSEnor.handle);	//50%�̉��ʂɂ���
						PlaySoundMem(BTSEnor.handle, DX_PLAYTYPE_BACK);
					}
					if (BEffectNormal.Viewimage < BEffectNormal.image.Divmax)
					{
						WaitTimer(100);
						BEffectNormal.Viewimage++;
					}
					else
					{
						BEffectNormal.isView = FALSE;
						BEffectNormal.Count = 0;
						BEffectNormal.Viewimage = 0;
						BEffectNormal.effectflg = 1;
					}
					break;
					case 1:
					int DAMAGEflag = Pstates.DAMAGE_CALC(Estates.DF, Estates.HP);
						if (Pstates.criflg == TRUE) {//�N���e�B�J��������
							Message = CRITICAL;
							if (UI.cricnt == 1)
							{WaitTimer(1000);}
							UI.cricnt++;
						}
						else{
							Message = GIVE_DAMAGE;
							if (UI.cricnt == 1)
							{WaitTimer(1000);}
							UI.cricnt++;
						}
						if (DAMAGEflag==1)//�G��|�����Ƃ�
						{
							
							Message = DEFEAT_EN;
							if (UI.Endefeatcnt == 1) { WaitTimer(2000); }
							Message = GET_EXP;
							if (UI.Endefeatcnt == 2) {
								WaitTimer(2000);
								Levelupflag = Pstates.LEVELUP();
								Pstates.EXP += Estates.EXP;
							}
							UI.Endefeatcnt=1;
							if (UI.Endefeatcnt>=3&&Levelupflag== TRUE)
							{//���x���A�b�v���̏��� 
								Message = Levelup;
								WaitTimer(1000);
								if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
								{
									Playendflag = 0;
									Playerflag = 2;
								}
							}
							else
							{
								if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
								{
									Playendflag = 0;
									Playerflag = 2;
								}
							}
						}
						else {
							Pstates.criflg = FALSE;
							Playerflag = 0;
							Battleflag = 1;
						}
						break;
					}
					//HP�𔻒肷��֐�
					break;
				case 1://�X�L��
					switch (skillflag) {
					case 0:
						UI.ENTER_COUNT_SKILL();
						if (CheckHitKey(KEY_INPUT_BACK) == TRUE)//�o�b�N�X�y�[�X���������Ƃ�
						{
							UI.count = 0;
							UI.Scount = 0;
							Playerflag = 0;
						}
						if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)//����������Ƃ�
						{
							if (UI.Skilltag == 0 || UI.Skilltag == 1) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag -= 2;
							}
						}
						if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)//�����������Ƃ�
						{
							if (UI.Skilltag == 2 || UI.Skilltag == 3) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag += 2;
							}
						}
						if ((CheckHitKey(KEY_INPUT_LEFT) == TRUE) && UI.CHANGE_COUNT() == TRUE)//�����������Ƃ�
						{
							if (UI.Skilltag == 0 || UI.Skilltag == 2) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag -= 1;
							}
						}
						if ((CheckHitKey(KEY_INPUT_RIGHT) == TRUE) && UI.CHANGE_COUNT() == TRUE)//�E���������Ƃ�
						{
							if (UI.Skilltag == 1 || UI.Skilltag == 3) {}
							else {
								PLAY_CARSOL_SOUND();
								UI.count = 0;
								UI.Skilltag += 1;
							}
						}
						if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.ENTER_COUNT_SKILL() == TRUE)//Enter���������Ƃ�
						{
							UI.Scount = 0;
							PLAY_ENTER_SOUND(DX_PLAYTYPE_BACK);
							skillflag = 1;
						}
						break;
					case 1:
						switch (UI.Skilltag)
						{
						case 0:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Iaiy2 -= UI.Iaiy2Move;
							}
							else {

							}
							break;
						case 1:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.KiKonx2 -= UI.KiKonx2Move;
								UI.KiKonx -= UI.KiKonxMove;
								UI.KiKony2 -= UI.KiKony2Move;
							}
							break;
						case 2:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Keny -= UI.KenyMove;
								UI.Keny2 -= UI.Keny2Move;
							}
							break;
						case 3:
							if (UI.SKILL_MOVE() == TRUE)
							{
								UI.Magicx -= UI.MagicxMove;
								UI.Magicx2 -= UI.Magicx2Move;
								UI.Magicy -= UI.MagicyMove;
								UI.Magicy2 -= UI.Magicy2Move;
							}
							break;
						}
						break;
					}
					break;
				case 2://�h��
				{
					//���݂̖h��l���L�^
					Pstates.OldbufDF = Pstates.bufDF;
					Pstates.OldbufMDF = Pstates.bufMDF;
					//�h��l��{�ɂ���
					Pstates.bufDF = Pstates.bufDF * 3;
					Pstates.bufMDF = Pstates.bufMDF * 3;
					Enemyflag = 1;
					Battleflag = 1;//�G�̃^�[����
				}
				break;
				case 3://�A�C�e��
					break;
				case 4://������
					Pstates.RUN_AWAY(Estates.AGI);
					if (Pstates.isRun == TRUE)
					{
						Playendflag = 0;
						Playerflag = 2;
					}
					else
					{
						Enemyflag = 0;
						Battleflag = 1;//�G�̃^�[����
					}
					break;
				}
				break;
			case 2://�s���I�����̏���
				switch (Playendflag)
				{
				case 0://���S�������̏���
					UI.BrightR -= 5, UI.BrightG -= 5, UI.BrightB -= 5;
					if (UI.BrightR < 0)
					{
						BATTLE_PROC_NEW();
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGM���~�߂�
						}
						GameScene = GAME_PLAY_SCENE;
					}
					break;
				case 1:
					UI.BrightR -= 5, UI.BrightG -= 5, UI.BrightB -= 5;
					if (UI.BrightR < 0)
					{
						BATTLE_PROC_NEW();
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGM���~�߂�
						}
						GameScene = GAME_PLAY_SCENE;
					}
				}
			
				break;
			}
			break;
		case 1://�G�̍s��
			switch (Enemyflag)
			{
			case 0://�ʏ�U��
				BEffectNormal.Count++;
				if (CheckSoundMem(BTSEENnor.handle) == 0 && BEffectNormal.Count > 60)
				{
					//BGM�̉��ʂ�������
					ChangeVolumeSoundMem(255 * 50 / 100, BTSEENnor.handle);	//50%�̉��ʂɂ���
					PlaySoundMem(BTSEENnor.handle, DX_PLAYTYPE_BACK);
					if (Pstates.DAMAGE_CALC(Pstates.bufDF, Pstates.HP) == 1)
					{
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGM���~�߂�
						}
						GameScene = GAME_END_SCENE;
					};
					BEffectNormal.Count = 0;
					Battleflag = 0;
					Playerflag = 0;
				}
				break;
			case 1:
				BEffectNormal.Count++;
				if (CheckSoundMem(BTSEENnor.handle) == 0 && BEffectNormal.Count > 60)
				{
					//BGM�̉��ʂ�������
					ChangeVolumeSoundMem(255 * 50 / 100, BTSEENnor.handle);	//50%�̉��ʂɂ���
					PlaySoundMem(BTSEENnor.handle, DX_PLAYTYPE_BACK);
					if (Pstates.DAMAGE_CALC(Pstates.bufDF, Pstates.HP) == 1) {
						if (CheckSoundMem(BTBGM1.handle) != 0)
						{
							StopSoundMem(BTBGM1.handle);	//BGM���~�߂�
						}
						GameScene = GAME_END_SCENE;
					};
					BEffectNormal.Count = 0;
					Pstates.bufDF = Pstates.OldbufDF;
					Pstates.bufMDF = Pstates.OldbufMDF;
					Battleflag = 0;
					Playerflag = 0;

				}
				break;
			}
			break;

		}
	}
	return;
}

VOID MY_BATTLE_DRAW()
{
		int Ename=GetDrawFormatStringWidth("%s", Estates.Name);
		SetDrawBright(UI.BrightR,UI.BrightG,UI.BrightB);//�o�g����ʂ̋P�x
		DrawGraph(btbk.x, btbk.y, btbk.handle, TRUE);//�o�g����ʂ̔w�i
		
		DrawGraph(enemy.x, 50, enemy.handle, TRUE);//�G�l�~�[�̉摜
		DrawFormatStringToHandle(enemy.x+enemy.width/2-Ename/2, 50, GetColor(255, 255, 255), tanu20.handle,
			"%s", Estates.Name);
		DrawGraph(250, 350, Bplayer.handle, TRUE);
		DrawFormatStringToHandle(250, 370
			, GetColor(255, 255, 255), tanu20.handle, "%s", Pstates.Name);
		/*DrawGraph(player.x, player.y, player.handle, TRUE);*/
		/*DrawBox(20, GAME_HEIGHT - 220, 220, GAME_HEIGHT-55, GetColor(255, 255, 0), TRUE);*/
		//UI
		DrawGraph(20, 370, UIback.handle, TRUE);
		DrawGraph(UI.UIx[0], 380, UI.image.UIhandle[0], TRUE);//�U��
		DrawGraph(UI.UIx[1], 420, UI.image.UIhandle[1], TRUE);//�X�L��
		DrawGraph(UI.UIx[2], 460, UI.image.UIhandle[2], TRUE);//�h��
		DrawGraph(UI.UIx[3], 500, UI.image.UIhandle[3], TRUE);//�A�C�e��
		DrawGraph(UI.UIx[4], 540, UI.image.UIhandle[4], TRUE);//������

		

		DrawBox(0, GAME_HEIGHT - 40, GAME_WIDTH, GAME_HEIGHT, GetColor(125, 125, 0), TRUE);
		
		//���b�Z�[�W�{�[�h
		if (UI.EncntUIisView == TRUE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawBox(0, 340, GAME_WIDTH,360,GetColor(200,200,200),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DRAW_MESSAGE(Message);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawBox(0, 340, GAME_WIDTH, 360, GetColor(200, 200, 200), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DRAW_MESSAGE(Message);
		}
		float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
		float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;

		float c = ((float)Estates.HP / (float)Estates.HPMAX) * 100;
		float d = ((float)Estates.MP / (float)Estates.MPMAX) * 100;
		//������HP
			DrawBox(350 - 2, 400 - 2, 350 + 100 + 2, 420 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 400, 350 + (int)a, 420, GetColor(0, 255, 95), TRUE);
			DrawFormatStringToHandle(350, 400
				, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.HP, Pstates.HPMAX);
			DrawBox(350 - 2, 425 - 2, 350 + 100 + 2, 445 + 2, GetColor(242, 242, 242), TRUE);
			DrawBox(350, 425, 350 + (int)b, 445, GetColor(30, 144, 255), TRUE);
			DrawFormatStringToHandle(350, 425
				, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.MP, Pstates.MPMAX);
			/*&& UI.UItag == 1)*/
			switch (Playerflag)
			{
			case 1:
				switch(UI.UItag)
				{ 
				case 1:
					switch (skillflag)
					{
					case 0:
						//����
						UI.SnameIAI = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname);
						DrawBox((int)UI.Iaix - 2, (int)UI.Iaiy - 2, (int)UI.Iaix2 + 2, (int)UI.Iaiy2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Iaix, (int)UI.Iaiy, (int)UI.Iaix2, (int)UI.Iaiy2, GetColor(170, 170, 170), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Iaix2 + (int)UI.Iaix) / 2 - UI.SnameIAI/2,
							((int)UI.Iaiy2+ (int)UI.Iaiy)/2-15
							, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname);
						//�����p
						UI.SnameKiKon = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname2);
						DrawBox((int)UI.KiKonx - 2, (int)UI.KiKony - 2, (int)UI.KiKonx2 + 2, (int)UI.KiKony2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.KiKonx, (int)UI.KiKony, (int)UI.KiKonx2, (int)UI.KiKony2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.KiKonx2 + (int)UI.KiKonx)/ 2 - UI.SnameKiKon / 2,
							((int)UI.KiKony2 + (int)UI.KiKony) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname2);
						//���p
						UI.SnameKen = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname3);
						DrawBox((int)UI.Kenx - 2, (int)UI.Keny - 2, (int)UI.Kenx2 + 2, (int)UI.Keny2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Kenx, (int)UI.Keny, (int)UI.Kenx2, (int)UI.Keny2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Kenx2 + (int)UI.Kenx) / 2 - UI.SnameKen / 2,
							((int)UI.Keny2 + (int)UI.Keny) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname3);
						//���@
						UI.SnameMagic = GetDrawFormatStringWidthToHandle(tanu30n.handle,
							"%s", Pstates.skillname4);
						DrawBox((int)UI.Magicx - 2, (int)UI.Magicy - 2, (int)UI.Magicx2 + 2, (int)UI.Magicy2 + 2, GetColor(242, 242, 242), TRUE);
						DrawBox((int)UI.Magicx, (int)UI.Magicy, (int)UI.Magicx2, (int)UI.Magicy2, GetColor(234, 85, 50), TRUE);
						DrawFormatStringToHandle(
							((int)UI.Magicx2 + (int)UI.Magicx) / 2 - UI.SnameMagic / 2,
							((int)UI.Magicy2 + (int)UI.Magicy) / 2 - 15, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname4);
						if (UI.Skilltag == 0)
						{
							DrawBox(480 - 2, 400 - 2, 710 + 2, 490 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 1)
						{
							DrawBox(720 - 2, 400 - 2, 950 + 2, 490 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 2)
						{
							DrawBox(480 - 2, 500 - 2, 710 + 2, 590 + 2, GetColor(255, 0, 0), FALSE);
						}
						if (UI.Skilltag == 3)
						{
							DrawBox(720 - 2, 500 - 2, 950 + 2, 590 + 2, GetColor(255, 0, 0), FALSE);
						}
						break;
					case 1:
						switch (UI.Skilltag)
						{
						case 0:
								//����
								DrawBox((int)UI.Iaix - 2, (int)UI.Iaiy - 2, (int)UI.Iaix2 + 2, (int)UI.Iaiy2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Iaix, (int)UI.Iaiy, (int)UI.Iaix2, (int)UI.Iaiy2, GetColor(170, 170, 170), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameIAI / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname);
								break;
						case 1:
								DrawBox((int)UI.KiKonx - 2, (int)UI.KiKony - 2, (int)UI.KiKonx2 + 2, (int)UI.KiKony2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.KiKonx, (int)UI.KiKony, (int)UI.KiKonx2, (int)UI.KiKony2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameKiKon / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname2);
								break;
						case 2:
								DrawBox((int)UI.Kenx - 2, (int)UI.Keny - 2, (int)UI.Kenx2 + 2, (int)UI.Keny2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Kenx, (int)UI.Keny, (int)UI.Kenx2, (int)UI.Keny2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameKen / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname3);
								break;
						case 3:
								DrawBox((int)UI.Magicx - 2, (int)UI.Magicy - 2, (int)UI.Magicx2 + 2, (int)UI.Magicy2 + 2, GetColor(242, 242, 242), TRUE);
								DrawBox((int)UI.Magicx, (int)UI.Magicy, (int)UI.Magicx2, (int)UI.Magicy2, GetColor(234, 85, 50), TRUE);
								DrawFormatStringToHandle(((int)UI.Iaix + (int)UI.Iaix2) / 2 - UI.SnameMagic / 2, 400
									, GetColor(255, 255, 255), tanu30n.handle, "%s", Pstates.skillname4);
								break;
						}
						break;
					}
					break;
				}
				break;
			}
		DrawBox(350 - 2, 200 - 2, 350 + 100 + 2, 220 + 2, GetColor(255, 255, 255), TRUE);
		DrawBox(350, 200, 350 + (int)c, 220, GetColor(0, 255, 0), TRUE);
		DrawFormatStringToHandle(350, 200
			, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Estates.HP, Estates.HPMAX);
		DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), tanu20.handle, "%s�͓����o�����I", Pstates.Name);
		if (BEffectNormal.isView == TRUE)//�ʏ�U���̃G�t�F�N�g�@
		{
			DrawGraph(enemy.x, enemy.y,
				BEffectNormal.image.Divhandle[BEffectNormal.Viewimage], TRUE);
		}

		DrawStringToHandle(320, GAME_HEIGHT - 30, "Enter:���� �\���L�[:�I�� Return:�L�����Z��", GetColor(255, 255, 255), tanu20.handle); return;
}



VOID MY_END()
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC()
{
	if (CheckSoundMem(OverBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, OverBGM.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(OverBGM.handle, DX_PLAYTYPE_LOOP);
	}
	return;
}
VOID MY_END_DRAW()
{
	DrawStringToHandle(0, 0, "���Ȃ��͕����܂���", GetColor(255, 255, 255), tanu20.handle);
	return;
}

void BATTLE_FLAG(int PAVI, int EAVI)//���x���r���Đ�U��U�𔻒f����֐�
{
	if (PAVI >= EAVI)
	{
		Battleflag = TRUE;//�v���C���[���U��
	}
	else
	{
		Battleflag = FALSE;//�G���U��
	}
}

VOID BATTLE_PROC_NEW(VOID)//�o�g���V�[��������������֐�
{
	Playerflag = 0;
	Playendflag = 0;
	UI.UItag = 0;
	UI.Mssgcount = 0;
	Battleflag = 0;
	Enemyflag = 0;
	skillflag = 0;
	UI.Skilltag = 0;
	UI.EncntUIisView = TRUE;
	UI.UIx[0] = UI.SpotUIx;
	UI.SKILL_MOVE_NEW();
	Message = ENCOUNT;
	for (int i = 1; i < 5; i++)
	{
		UI.UIx[i] = UI.NonSpotUIx;
	}
	return;
}

VOID INPUTBTLSTATES_BUF()//��퓬�p�ɃX�e�[�^�X��ޔ�������֐�
{
	Pstates.bufAT = Pstates.AT;
	Pstates.bufDF = Pstates.DF;
	Pstates.bufMDF = Pstates.MDF;
	Pstates.bufAGI = Pstates.AGI;
	return;
}

BOOL LOADING_FULL_IMAGE(VOID)//�摜�S�Ă����[�h����֐�
{
	if (title.LOADING_IMAGE(IMAGE_TITLE) == -1) { return FALSE; }
	if (Bplayer.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return FALSE; }
	/*if (player.image.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == FALSE) { return FALSE; }*/
	if (player.image.LOADING_DIV_IMAGE(DIV_CHARA_TATE, DIV_CHARA_YOKO, MAP_DIV_WIDTH,
		MAP_DIV_HEIGHT, IMAGE_PLAYER_INMAP) == -1) {
		return FALSE;
	}
	if (BEffectNormal.image.LOADING_DIV_IMAGE(DIV_BT_EFFECT_TATE, DIV_BT_EFFECT_YOKO,
		DIV_BT_EFFECT_WIDTH, DIV_BT_EFFECT_HEIGHT, IMAGE_BATTLE_EFFECT_NORMAL_AT) == -1)
	{
		return FALSE;
	}
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return FALSE; }
	if (btbk.LOADING_IMAGE(IMAGE_BATTLE_BACK) == -1) { return FALSE; }
	if (UIback.LOADING_IMAGE(IMAGE_UI_BACK) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_KOUGEKI, 0) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_SKILL, 1) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_GUARD, 2) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_ITEM, 3) == -1) { return FALSE; }
	if (UI.image.LOADING_IMAGE(IMAGE_UI_RUN, 4) == -1) { return FALSE; }
	//�X�^�[�g���
	if (titlelogo.LOADING_IMAGE(IMAGE_START_ROGO) == -1) { return FALSE; }
	//�X�e�[�^�X���
	if (S_UI.charaimg.LOADING_IMAGE(IMAGE_STATES_CHARA) == -1) { return FALSE; }
	if (S_UI.UIimg.LOADING_IMAGE(IMAGE_STATES_UI_ST, 0) == -1) { return FALSE; }
	if (S_UI.back.LOADING_IMAGE(IMAGE_STATES_BACK) == -1) { return FALSE; }
	if (S_UI.back2.LOADING_IMAGE(IMAGE_STATES_BACK2) == -1) { return FALSE; }
	//�C�x���g���
	if (eventS.txtUI.LOADING_IMAGE(IMAGE_EVENT_TXTUIBACK) == -1) { return FALSE; }
	return TRUE;
}

VOID LOADING_FULL_MAP()
{
	divmap.DIV_MAP();
	MAPUND.LOADING_MAP(GAME_MAP1_UNDER_TXT);//���̃}�b�v
	MAPUND.MAPSETTING(divmap.width, divmap.height);
	MAPMID.LOADING_MAP(GAME_MAP1_MIDDLE_TXT);//���̃}�b�v
	MAPMID.MAPSETTING(divmap.width, divmap.height);
	MAPON.LOADING_MAP(GAME_MAP1_ON_TXT);//��̃}�b�v
	MAPON.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.LOADING_MAP(GAME_MAP1_HITBOX);//�����蔻��̃}�b�v
	MAPHIT.MAPSETTING(divmap.width, divmap.height);
	MAPHIT.SETTING_HITBOX(divmap.width, divmap.height);
	MAPEN.LOADING_MAP(GAME_MAP1_ENEMYMAP);//�G�̏o���}�b�v
	MAPEN.MAPSETTING(divmap.width, divmap.height);
	MAPEN.SETTING_HITBOX(divmap.width, divmap.height);
	return;
}

VOID CREATE_FULL_FONT()
{
	tanu20.CREATE_FONT(20, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30.CREATE_FONT(30, FONT_TANU_PATH, FONT_TANU_NAME);
	tanu30n.CREATE_FONT_NONEDGE(30, FONT_TANU_PATH, FONT_TANU_NAME);
	return;
}

BOOL LOADING_FULL_MUSIC()
{
	if (TitleBGM.LOAD_MUSIC(TITLE_SCENE_MUSIC) == FALSE) { return -1; }
	if (PlayBGM.LOAD_MUSIC(PLAY_SCENE_MUSIC) == FALSE) { return -1; }
	if (BTBGM1.LOAD_MUSIC(BATTLE_SCENE_MUSIC1) == FALSE) { return -1; }
	if (BTSEnor.LOAD_MUSIC(BATTLE_SE_NORMALAT) == FALSE) { return -1; }
	if (BTSEENnor.LOAD_MUSIC(BATTLE_SE_EN_NORMAL_AT) == FALSE) { return -1; }
	if (OverBGM.LOAD_MUSIC(END_SCENE_MUSIC_OVER) == FALSE) { return -1; }
	if (BTcar.LOAD_MUSIC(BATTLE_SE_CARSOL) == FALSE) { return -1; }
	if (BTenter.LOAD_MUSIC(BATTLE_SE_ENTER) == FALSE) { return -1; }
	return TRUE;
}

VOID PLAY_CARSOL_SOUND()
{
	ChangeVolumeSoundMem(255 * 50 / 100, BTcar.handle);	//50%�̉��ʂɂ���
	PlaySoundMem(BTcar.handle, DX_PLAYTYPE_BACK);
	return;
}

VOID PLAY_ENTER_SOUND(int playtype)
{
	ChangeVolumeSoundMem(255 * 50 / 100, BTenter.handle);	//50%�̉��ʂɂ���
	PlaySoundMem(BTenter.handle, playtype);
	return;
}

VOID DRAW_MESSAGE(int mestype)
{
	switch (mestype)
	{
	case ENCOUNT:
		DrawFormatStringToHandle(0, 340, GetColor(255, 255, 255), tanu20.handle,
			"%s�������ꂽ�I", Estates.Name);
		return;
		break;
	case SELECT_NORMAL_AT:
		DrawStringToHandle(0, 340, "�ʏ�U�����s���܂�", C.White, tanu20.handle);
		return;
		break;
	case NORMAL_AT:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%s�̂��������I", Pstates.Name);
		return;
		break;
	case SKILL:
		DrawStringToHandle(0, 340, "�X�L����I�����čU�����܂�", C.White, tanu20.handle);
		return;
		break;
	case GUARD:
		DrawStringToHandle(0, 340, "�U���������ɖh�䂵�܂�", C.White, tanu20.handle);
		return;
		break;
	case SELECT_ITEM:
		DrawStringToHandle(0, 340, "�A�C�e����I�����Ďg�p���܂�", C.White, tanu20.handle);
		return;
		break;
	case RUN:
		DrawStringToHandle(0, 340, "�����Ă��̏ꂩ�瓦���܂��B���s���邱�Ƃ��c", C.White, tanu20.handle);
		return;
		break;
	case CRITICAL:
		DrawStringToHandle(0, 340, "�}����˂����I", C.White, tanu20.handle);
		return;
		break;
	case DEFEAT_EN:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%s��|�����I", Estates.Name);
		return;
		break;
	case GET_EXP:
		DrawFormatStringToHandle(0, 340, GetColor(255,255,255), tanu20.handle,
			"%d�o���l���l��", Estates.EXP);
		return;
		break;
	case GIVE_DAMAGE:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"%d�_���[�W��^�����I", Pstates.damage);
		return;
		break;
	case Levelup:
		DrawFormatStringToHandle(0, 340, C.White, tanu20.handle,
			"���x����%d�オ�����IHP+%d MP+%d �U����+%d ���@�U����+%d ���΂₳+%d �h���+%d ���@�h���+%d",
			Pstates.bLv, Pstates.bHPMAX, Pstates.bMPMAX, Pstates.bSTR, Pstates.bMSTR);
	}
}