#pragma once
#define ITEMNUM 30
#define ITEMNAME 30

class ITEM
{
public:
	int healPoint;
	char Name[10];
	int tag = 0;
	int heal[ITEMNUM];
	int htag[ITEMNUM];
	char hName[ITEMNUM][ITEMNAME];
	void INPUTSTATES_SYUDOU(int,char,int);
	void INPUTITEM_HEAL(int,char,int,const char*);
};

void ITEM::INPUTSTATES_SYUDOU(int Point,char ch,int tag)
{
	healPoint = Point;
	Name[0] = ch;
	this->tag = tag;
};

void ITEM::INPUTITEM_HEAL(int Point, char ch, int tag,const char* statespath)
{
	int ret;
	int n = 0;
	FILE* fp = fopen(statespath, "r");
	while (ret = fscanf(fp, "%d,%s,%d,",
		&heal[n],&hName[n],&htag[n],n++) != EOF) {};
	fclose(fp);
}
