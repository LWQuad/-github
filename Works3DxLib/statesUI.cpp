#include "statesUI.hpp"

BOOL STATES_UI::UI_MOVE()//UI�̍��ڈړ���҂֐�
{
	Ccount++;
	if (Ccount > CcountMAX)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL STATES_UI::CHANGE_STorPLAY()//UI�̍��ڈړ���҂֐�
{
	Scount++;
	if (Scount > ScountMAX)
	{
		return TRUE;
	}
	return FALSE;
}
