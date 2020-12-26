#pragma once
#include "image.hpp"
#include <vector>
#include <string>
#define EVENT_TXT_SAMPLE TEXT(".\\EVENTtxt\\ƒTƒ“ƒvƒ‹.txt")
#define EVENT_TXT TEXT(".\\EVENTtxt\\EVENT1.txt")

using namespace std;
#define LINE_MAX 100
#define MOZI_MAX 100

class EVENT
{
public:
	int count=0;
	int countMax = 30;
	int strLnum = 0;
	char str[LINE_MAX][MOZI_MAX];
	LOAD_SINGLE_IMAGE txtUI;
	BOOL INPUTTXT(const char*);
};

