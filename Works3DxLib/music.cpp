#include "music.hpp"

BOOL MUSIC::LOAD_MUSIC(const char* musicpath)
	{
	strcpy_s(path, musicpath);				//�p�X�̐ݒ�
	handle = LoadSoundMem(path);			//�ǂݍ���
	if (handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), musicpath, "���y�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	return TRUE;
	}
