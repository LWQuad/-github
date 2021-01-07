#include "statesUI.hpp"

BOOL STATES_UI::UI_MOVE()//UI‚Ì€–ÚˆÚ“®‚ð‘Ò‚ÂŠÖ”
{
	Ccount++;
	if (Ccount > CcountMAX)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL STATES_UI::CHANGE_STorPLAY()//UI‚Ì€–ÚˆÚ“®‚ð‘Ò‚ÂŠÖ”
{
	Scount++;
	if (Scount > ScountMAX)
	{
		return TRUE;
	}
	return FALSE;
}
