#include "event.hpp"

BOOL EVENT::INPUTTXT(const char* txt)
{
	ifstream ifs(txt);
	string str;
	int Line = 0;
	while (getline(ifs, str))
	{
		strcpy_s(this->str[Line], str.c_str());
		Line++;
		if (Line > LINE_MAX-1)//ヤバいエラーが出るので徹底して残しましょう
		{
			Line = LINE_MAX - 1;
			break;
		}
	}
	ifs.close();
	return TRUE;
}
