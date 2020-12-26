#include "DxLib.h"
#include "image.hpp"
#include "windowsystem.h"
#include "map.hpp"

BOOL LOAD_SINGLE_IMAGE::LOADING_IMAGE(const char* pathname)
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

BOOL LOAD_SINGLE_IMAGE::LOADING_IMAGE(const char* pathname,int handleNum)
{
	strcpy(this->path, pathname);
	this->UIhandle[handleNum] = LoadGraph(this->path);			//�ǂݍ���
	if (this->UIhandle[handleNum] == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), pathname, "�摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	GetGraphSize(this->UIhandle[handleNum], &this->width, &this->height);	//�摜�̕��ƍ������擾
	handle = LoadGraph(this->path);
	GetGraphSize(UIhandle[handleNum], &this->width, &this->height);
	this->x = GAME_WIDTH / 2 - this->width / 2;		//���E��������
	this->y = GAME_HEIGHT / 2 - this->height / 2;		//�㉺��������
	return TRUE;
}

BOOL LOAD_DIV_IMAGE::LOADING_DIV_IMAGE(int divtate,int divyoko,int divwidth,int divheight,
const char* divimagepath)
{
	int divmax = divtate * divyoko;
	this->Divmax = divmax - 1;
	this->Divhandle.resize(divmax);//�������ɍ��킹�ăn���h�����𑝂₷
	int mapRes = LoadDivGraph(
		divimagepath,										//�}�b�v�̃p�X
		divmax, divtate, divyoko,			//�}�b�v�𕪊����鐔
		divwidth, divheight,						//�摜�𕪊����镝�ƍ���
		&this->Divhandle[0]);								//���������摜������n���h��
	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "�L�����摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(this->Divhandle[0], &this->width, &this->height);
	return TRUE;
}

