#include "DxLib.h"
#include "map.hpp"

VOID MAPINPUT::RESIZE(int TATE_MAX, int YOKO_MAX)
{
	kind.resize(TATE_MAX, vector<int>(YOKO_MAX));
	width.resize(TATE_MAX, vector<int>(YOKO_MAX));
	height.resize(TATE_MAX, vector<int>(YOKO_MAX));
	x.resize(TATE_MAX, vector<int>(YOKO_MAX));
	y.resize(TATE_MAX, vector<int>(YOKO_MAX));
	mapF.resize(TATE_MAX, vector<int>(YOKO_MAX));
	map.resize(TATE_MAX, vector<int>(YOKO_MAX));
	return;
}

BOOL MAPINPUT::LOADING_MAP(const char* maptxt)//�}�b�v�f�[�^��ǂݍ��ފ֐�(�}�b�v�t�@�C���p�X)
{
	//ifstream ifs(maptxt);
	//string str;
	//int tate = 0, yoko = 0;
	//while (getline(ifs, str, ','))
	//{
	//	this->map[tate][yoko] = atoi(str.c_str());
	//	yoko++;
	//	if (yoko > MAP_YOKO_MAX1 - 1) { yoko = 0; tate++; }
	//}
	//ifs.close();
	ifstream ifs(maptxt);
	string str;
	int tate = 0, yoko = 0;
	while (getline(ifs, str))
	{
		string tmp = "";
		istringstream stream(str);
		while (getline(stream, tmp, ','))
		{
			this->map[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
	}
	ifs.close();
	return TRUE;
}

VOID MAPINPUT::MAPSETTING(int chipwidth, int chipheight)
//�}�b�v�f�[�^�̍��W��ݒ肷��֐�(�}�b�v�`�b�v�̕��A�}�b�v�`�b�v�̍���)
{
	

	for (int tate = 0; tate < MAP_TATE_MAX1; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX1; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			this->mapF[tate][yoko] = this->map[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			this->kind[tate][yoko] = this->map[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			this->width[tate][yoko] = chipwidth;
			this->height[tate][yoko] = chipheight;

			//�}�b�v�̍��W��ݒ�
			this->x[tate][yoko] =(yoko * this->width[tate][yoko]);
			this->y[tate][yoko] =(tate * this->height[tate][yoko]);
			this->x[tate][yoko] -= 10 * chipwidth;
			this->y[tate][yoko] -= 20 * chipheight;
			this->isVIEW = FALSE;
		}
	}
	return;
}



BOOL MAP_DIV::DIV_MAP(const char* path,int div_tate,int div_yoko,int div_scale) {
	
	int div_num = div_tate * div_yoko;
	handle.resize(div_num), kind.resize(div_num);
	int mapRes = LoadDivGraph(
		path,										//�}�b�v�̃p�X
		div_num, div_tate, div_yoko,			//�}�b�v�𕪊����鐔
		div_scale, div_scale,						//�摜�𕪊�����̕��ƍ���
		&this->handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH1, "�}�b�v�摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;

}
