#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "image.hpp"
using namespace std;

#define ITEMNUM 10
#define ITEM_FILE_PATH TEXT(".\\ITEM\\Item.csv")



class ITEM
{
public:
	LOAD_DIV_IMAGE image;
	vector<int> healHP, healMP, tag, buy, sell, have;
	vector<float> goodhosei, badhosei;
	char Name[ITEMNUM][30], Expl[ITEMNUM][5][160], badStatus[ITEMNUM][30], goodStatus[ITEMNUM][30];
	BOOL INPUTITEM_HEAL(const char*);
	VOID GET_ITEM(int);
	
	//�A�C�e���̏���ǂݍ��ފ֐�
};

BOOL ITEM::INPUTITEM_HEAL(const char* itempath)//�}�b�v�f�[�^��ǂݍ��ފ֐�(�}�b�v�t�@�C���p�X)
{
	ifstream ifs(itempath);
	string str, strexpl;
	int colunm = 0, line = 0;
	while (getline(ifs, str))
	{
		int i = 0;
		string tmp = "";
		istringstream stream(str);
		while (getline(stream, tmp, ','))
		{
			string expltmp = "";
			istringstream explstream(tmp);
			switch (colunm) {
			case 0://���O��ǂݍ���
				strcpy_s(Name[line], tmp.c_str());
				break;
			case 1://������ǂݍ���
				while (getline(explstream, expltmp, '@'))
				{
					strcpy_s(Expl[line][i], expltmp.c_str());
					i++;
				}
				i = 0;
				break;
			case 2://�^�O��ǂݍ���
				tag.push_back(atoi(tmp.c_str()));
				break;
			case 3://HP�񕜗ʂ�ǂݍ���
				healHP.push_back(atoi(tmp.c_str()));
				break;
			case 4://MP�񕜗ʂ�ǂݍ���
				healMP.push_back(atoi(tmp.c_str()));
				break;
			case 5://GOODSTATUS
				strcpy_s(goodStatus[line], tmp.c_str());
				break;
			case 6://BADSTATUS
				strcpy_s(badStatus[line], tmp.c_str());
				break;
			case 7://�w���z
				buy.push_back(atoi(tmp.c_str()));
				break;
			case 8://���p�z
				sell.push_back(atoi(tmp.c_str()));
				break;
			case 9://������
				have.push_back(atoi(tmp.c_str()));
				break;
			case 10://�o�t�␳
				goodhosei.push_back(atoi(tmp.c_str()));
				break;
			case 11://�f�o�t�␳
				badhosei.push_back(atoi(tmp.c_str()));
				break;
			}
			colunm++;
		}
		line++;
		colunm = 0;
	}
	ifs.close();
	return TRUE;
}

VOID ITEM::GET_ITEM(int Num)
{
	return;
}