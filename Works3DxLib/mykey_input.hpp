#pragma once
#include "DxLib.h"

class KEYINPUT
{
private:
	char AllKeyState[256];
	char OldKeyState[256];
	BOOL OnlyKeyflg[256] = { TRUE };

public:
	//�L�[�̃C���v�b�g�����Ǘ�����
	/* 0: ��x���� */
	int KEYINPUT_ALLACTION(int);
	int KEYINPUT_NORMAL(int);
	int KEYINPUT_UP(int);
};
