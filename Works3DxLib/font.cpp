#include "font.hpp"

BOOL CREATE_FONTHANDLE::CREATE_FONT(int fontsize,const char* fontpath,const char* fontname)
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
