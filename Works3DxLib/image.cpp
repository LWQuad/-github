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


