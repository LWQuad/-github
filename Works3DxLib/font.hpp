#pragma once
#include <iostream>
#include "DxLib.h"
#include "windowsystem.h"
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

class CREATE_FONTHANDLE
{
public:
	char path[PATH_MAX];		//�p�X
	char name[NAME_MAX];		//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v

	BOOL CREATE_FONT(int, const char*, const char*);
	BOOL CREATE_FONT_NONEDGE(int, const char*, const char*);
	//�t�H���g�n���h���̍쐬
	//(�t�H���g�T�C�Y�@�t�H���g�̃p�X�@�t�H���g�̖��O)

	~CREATE_FONTHANDLE()//�t�H���g�n���h�����폜
	{
		DeleteFontToHandle(this->handle);
	}
};
