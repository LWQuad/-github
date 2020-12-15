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

BOOL LOAD_DIV_IMAGE::LOADING_DIV_IMAGE(const char* divimagepath)
{
	int mapRes = LoadDivGraph(
		divimagepath,										//�}�b�v�̃p�X
		DIV_CHARA, DIV_CHARA_TATE, DIV_CHARA_YOKO,			//�}�b�v�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&this->handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "�L�����摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;
}

