#pragma once
#include <iostream>
#include "DxLib.h"

class BATTLE_UI
{
private:
	int KOUGEKI = 0;
	int SKILL = 1;
	int GUARD = 2;
	int ITEM = 3;
	int RUN = 4;//���ڈړ�����^�O
	int countMAX = 20;
public:
	int count = 0;
	int UItag = 0;//UI�̍��ڂ��Ǘ�����
	BOOL CHANGE_COUNT();
};

BOOL BATTLE_UI::CHANGE_COUNT()//UI�̍��ڈړ���҂֐�
{
	count++;
	if (count > countMAX)
	{
		return TRUE;
	}
	return FALSE;
}
