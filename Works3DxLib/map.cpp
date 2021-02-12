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

BOOL MAPINPUT::LOADING_MAP_TAG(int saveslot,const char* maptagpath)
{
	int ret;
	FILE* fp = fopen(maptagpath, "r");
	while (ret = fscanf(fp, "%d,",
		&MAPtag[saveslot]) != EOF) {};
	return TRUE;
}

BOOL MAPINPUT::LOADING_MAP_COORDINATES(const char* maptxtX,const char* maptxtY)
//�}�b�v�f�[�^�̍��W��ǂݍ��ފ֐�(X���W�̃t�@�C���p�X�AY���W�̃t�@�C���p�X)
{
	ifstream ifsX(maptxtX),ifsY(maptxtY);
	string strX, strY;
	int tate = 0, yoko = 0;
	while (getline(ifsX, strX))
	{
		string tmp = "";
		istringstream stream(strX);
		while (getline(stream, tmp, ','))
		{
			this->x[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
	}
	tate = 0, yoko = 0;
	while (getline(ifsY, strY))
	{
		string tmp = "";
		istringstream stream(strY);
		while (getline(stream, tmp, ','))
		{
			this->y[tate][yoko] = atoi(tmp.c_str());
			yoko++;
		}
		yoko = 0;
		tate++;
	}
	ifsX.close(),ifsY.close();
	return TRUE;
}

//�}�b�v�̍��W��ۑ�����֐�
BOOL MAPINPUT::SAVE_MAP(int TATE_MAX, int YOKO_MAX,const char* mapdatapathX,const char* mapdatapathY,
	const char* maptagpath)
{
	ofstream ofsX(mapdatapathX), ofsY(mapdatapathY), ofsTag(maptagpath);
	if (!ofsX||!ofsY)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), ERROR_MESSAGE, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
		{
			ofsX << this->x[tate][yoko]<<",";
			ofsY << this->y[tate][yoko]<<",";
		}
		ofsX << endl;
		ofsY << endl;
	}
	if (TATE_MAX == MAP_FOREST_TATEMAX && YOKO_MAX == MAP_FOREST_YOKOMAX) {
		ofsTag << 1 << endl;
	}
	return TRUE;
}

//�}�b�v�f�[�^�̍��W��ݒ肷��֐�(�}�b�v�`�b�v�̕��A�}�b�v�`�b�v�̍���)
VOID MAPINPUT::MAPSETTING(int chipwidth, int chipheight,int Stx,int Sty,int TATE_MAX,int YOKO_MAX)
{
	

	for (int tate = 0; tate < TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < YOKO_MAX; yoko++)
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
			this->x[tate][yoko] -= Stx;
			this->y[tate][yoko] -= Sty;
			this->isVIEW = FALSE;
		}
	}
	return;
}

VOID MAPINPUT::INTARACTIV_MAP(int TATE_MAX, int YOKO_MAX)
{
	mapmove++;
	if (mapmove==10)
	{
		for (int tate = 0; tate < TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < YOKO_MAX; yoko++)
			{
				//�}�b�v��`��
				if (kind[tate][yoko] == 1460)
				{
					kind[tate][yoko] = 1461;
				}
			}
		}
	}
	if (mapmove==20)
	{
		for (int tate = 0; tate < TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < YOKO_MAX; yoko++)
			{
				//�}�b�v��`��
				if (kind[tate][yoko] == 1461)
				{
					kind[tate][yoko] = 1460;
				}
			}
		}
		mapmove = 0;
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
		MessageBox(GetMainWindowHandle(), ERROR_MESSAGE, "�}�b�v�摜�̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(this->handle[0], &this->width, &this->height);
	return TRUE;

}
