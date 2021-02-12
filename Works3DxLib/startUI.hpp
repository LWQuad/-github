#pragma once
#include "image.hpp"
#include "DxLib.h"
class START_UI
{
private:
public:
	int DataTag = 0, tag = 0;
	int Startflg = 0, Movelogoflg = 0;
	int SaveData1x = 320, SaveData1y = 224;
	int SaveData1x2=640, SaveData1y2=320;
	int SaveData2y = SaveData1y2 + 32, SaveData2y2 = SaveData2y + 96;
	int SaveData3y = SaveData2y2 + 32, SaveData3y2 = SaveData3y + 96;
	int Carsolx, Carsoly, Carsolx2, Carsoly2;
};

