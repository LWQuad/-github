#pragma once
class ITEM
{
public:
	int healPoint;
	char Name[10];
	int tag = 0;
	void INPUTSTATES_SYUDOU(int,char,int);
};

void ITEM::INPUTSTATES_SYUDOU(int Point,char ch,int tag)
{
	healPoint = Point;
	Name[0] = ch;
	this->tag = tag;
};
