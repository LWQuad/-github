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
#include <iostream>
#include <string>
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
	GAME_END_SCENE
};

class HPbar
{
	int HPwidth = 100;
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
LOAD_SINGLE_IMAGE Bplayer;
LOAD_SINGLE_IMAGE enemy;
LOAD_SINGLE_IMAGE btbk;
LOAD_SINGLE_IMAGE UIback;
LOAD_SINGLE_IMAGE kougekiUI;
LOAD_SINGLE_IMAGE skillUI;
CREATE_FONTHANDLE tanu20;
CREATE_FONTHANDLE tanu30;
MAP_DIV divmap;
MAPINPUT MAPUND;
MAPINPUT MAPMID;
MAPINPUT MAPON;
MAP_HITBOX MAPHIT;
MAP_ENEMY MAPEN;
ENEMY Senemy;
CHARA player;

BATTLE_UI UI;
int GameScene;//�Q�[���V�[�����Ǘ�����
int MoveMap = 0;

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
	if (Bplayer.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }
	/*if (player.image.LOADING_IMAGE(IMAGE_PLAYER_BATTLE) == -1) { return -1; }*/
	if (player.image.LOADING_DIV_IMAGE(IMAGE_PLAYER_INMAP) == -1) { return -1; }
	if (enemy.LOADING_IMAGE(IMAGE_ENEMY1) == -1) { return -1; }
	if (btbk.LOADING_IMAGE(IMAGE_BATTLE_BACK) == -1) { return -1; }
	if (UIback.LOADING_IMAGE(IMAGE_UI_BACK) == -1) { return -1; }
	if (kougekiUI.LOADING_IMAGE(IMAGE_UI_KOUGEKI) == -1) { return -1; }
	if (skillUI.LOADING_IMAGE(IMAGE_UI_SKILL) == -1) { return -1; }
	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

	GameScene = GAME_PLAY_SCENE;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��
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

	//start�ʒu�̐ݒ�
	player.image.x = divmap.width*10; player.image.y =divmap.height*11 ;
	player.Nowhandle = player.image.handle[0];
	/*player.image.IsDraw = TRUE;*/
	//�X�^�[�g�����܂��Ă��Ȃ����
	//if (startPt.x == -1 && startPt.y == -1)
	//{
	//	//�G���[���b�Z�[�W�\��
	//	MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	//}
	Pstates.INPUT_STATES(PLAYER_STATES);
	////�S�[�������܂��Ă��Ȃ����
	//if (GoalRect.left == -1)
	//{
	//	//�G���[���b�Z�[�W�\��
	//	MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	//}
	tanu20.CREATE_FONT(20,FONT_TANU_PATH,FONT_TANU_NAME);
	tanu30.CREATE_FONT(30, FONT_TANU_PATH, FONT_TANU_NAME);
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
		player.Nowhandle = player.image.handle[10];
		player.coll.top -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else{ player.image.y -= 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{GameScene = GAME_BATTLE_SCENE;}
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
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE )
	{
		/*player.image.x -= 5;*/
		player.Nowhandle = player.image.handle[4];
		player.coll.left -= 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else {
			player.image.x -= 5;
		}
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
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
				}
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE)
	{
		player.Nowhandle = player.image.handle[1];
		player.coll.bottom += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{}
		else { player.image.y += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
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
				}
			}
		}

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		player.Nowhandle = player.image.handle[7];
		player.coll.right += 5;
		if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE){}
		else { player.image.x += 5; }
		if (MAPEN.MY_CHECK_ENEMY_PLAYER_COLL(player.coll) == 1)
		{
			GameScene = GAME_BATTLE_SCENE;
		}
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
				}
			}
		}
	}
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x > GAME_WIDTH-divmap.width) { player.image.x = GAME_WIDTH - divmap.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y > GAME_HEIGHT - divmap.height) { player.image.y = GAME_HEIGHT - divmap.height; }
	//player.coll.left = player.image.x + 5;
	//player.coll.top = player.image.y + 5;
	//player.coll.right = player.image.x + player.image.width - 5;
	//player.coll.bottom = player.image.y + player.image.height - 5;
	//if (MAPHIT.MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	//{
	//	player.image.x = player.OldX;
	//	player.image.y = player.OldY;
	//}





	return;
}
VOID MY_PLAY_DRAW()
{
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
	}
	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
{
	for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
	{
		//�ǂȂ��
		if (MAPHIT.kind[tate][yoko] == 63)
		{
			DrawBox(MAPHIT.Hitmap[tate][yoko].left, MAPHIT.Hitmap[tate][yoko].top,
				MAPHIT.Hitmap[tate][yoko].right, MAPHIT.Hitmap[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
		}

	}
}
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
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
	UI.CHANGE_COUNT();
	if ((CheckHitKey(KEY_INPUT_UP) == TRUE) && UI.CHANGE_COUNT() == TRUE)
	{
		UI.count = 0;
		UI.UItag -= 1;
		if (UI.UItag < 0) { UI.UItag = 4; }
	}
	if ((CheckHitKey(KEY_INPUT_DOWN) == TRUE) && UI.CHANGE_COUNT() == TRUE)
	{
		UI.count = 0;
		UI.UItag += 1;
		if (UI.UItag > 4) { UI.UItag = 0; }
	}

	if ((CheckHitKey(KEY_INPUT_RETURN) == TRUE) && UI.UItag == 0)//�U���I����
	{

	}
	return;
}

VOID MY_BATTLE_DRAW()
{
	DrawGraph(btbk.x, btbk.y, btbk.handle, TRUE);
	DrawGraph(enemy.x, enemy.y, enemy.handle, TRUE);
	DrawGraph(200, 370, Bplayer.handle, TRUE);
	/*DrawGraph(player.x, player.y, player.handle, TRUE);*/
	/*DrawBox(20, GAME_HEIGHT - 220, 220, GAME_HEIGHT-55, GetColor(255, 255, 0), TRUE);*/
	DrawGraph(20, 330, UIback.handle, TRUE);
	/*DrawStringToHandle(30, 400, "�Z�U��", GetColor(255, 255, 255), tanu30.handle);*/
	DrawGraph(30, 340, kougekiUI.handle, TRUE);
	DrawGraph(30, 380, kougekiUI.handle, TRUE);
	DrawGraph(30, 420, kougekiUI.handle, TRUE);
	DrawGraph(30, 460, kougekiUI.handle, TRUE);
	DrawGraph(30, 500, kougekiUI.handle, TRUE);
	/*DrawStringToHandle(30, 460, "�Z�h��", GetColor(255, 255, 255), tanu30.handle);
	DrawStringToHandle(30, 490, "�Z�A�C�e��", GetColor(255, 255, 255), tanu30.handle);
	DrawStringToHandle(30, 520, "�Z�ɂ���", GetColor(255, 255, 255), tanu30.handle);*/
	DrawBox(0, GAME_HEIGHT - 40, GAME_WIDTH, GAME_HEIGHT, GetColor(125, 125, 0), TRUE);
	DrawBox(350-2, 400-2, 350 + 100+2, 420+2, GetColor(255, 255, 255), TRUE);
	float a = ((float)Pstates.HP / (float)Pstates.HPMAX) * 100;
	float b = ((float)Pstates.MP / (float)Pstates.MPMAX) * 100;
	DrawBox(350, 400,350+(int)a, 420, GetColor(0, 255, 0), TRUE);
	DrawStringToHandle(320, GAME_HEIGHT-30, "Enter:���� �\���L�[:�I�� Return:�L�����Z��", GetColor(255, 255, 255), tanu20.handle);
	DrawFormatStringToHandle(350, 400
		, GetColor(255, 255, 255), tanu20.handle, "%d/%d", Pstates.HP, Pstates.HPMAX);
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

