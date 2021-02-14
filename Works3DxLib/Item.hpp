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
	
	//アイテムの情報を読み込む関数
};

BOOL ITEM::INPUTITEM_HEAL(const char* itempath)//マップデータを読み込む関数(マップファイルパス)
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
			case 0://名前を読み込む
				strcpy_s(Name[line], tmp.c_str());
				break;
			case 1://説明を読み込む
				while (getline(explstream, expltmp, '@'))
				{
					strcpy_s(Expl[line][i], expltmp.c_str());
					i++;
				}
				i = 0;
				break;
			case 2://タグを読み込む
				tag.push_back(atoi(tmp.c_str()));
				break;
			case 3://HP回復量を読み込む
				healHP.push_back(atoi(tmp.c_str()));
				break;
			case 4://MP回復量を読み込む
				healMP.push_back(atoi(tmp.c_str()));
				break;
			case 5://GOODSTATUS
				strcpy_s(goodStatus[line], tmp.c_str());
				break;
			case 6://BADSTATUS
				strcpy_s(badStatus[line], tmp.c_str());
				break;
			case 7://購入額
				buy.push_back(atoi(tmp.c_str()));
				break;
			case 8://売却額
				sell.push_back(atoi(tmp.c_str()));
				break;
			case 9://所持数
				have.push_back(atoi(tmp.c_str()));
				break;
			case 10://バフ補正
				goodhosei.push_back(atoi(tmp.c_str()));
				break;
			case 11://デバフ補正
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