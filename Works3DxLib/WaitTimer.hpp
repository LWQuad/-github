#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "windowsystem.h"
#include "DxLib.h"
#include <string>

class WaitingTime
{
private:
    BOOL Throughflg = FALSE;
public:
	//DrawÇ…àÍìxï`âÊÇµÇΩÇÃÇøÅià¯êîÅjïbë“Ç¬ä÷êî
	BOOL WaitTime_OneThrough(int);
	VOID WaitTime_New();
};

class SINGLE_TASK
{
private:
	BOOL Singleflg = TRUE;
public:
	BOOL Single_Task();
	VOID Remove_Task();
};

BOOL SINGLE_TASK::Single_Task()
{
	if (Singleflg == TRUE)
	{
		Singleflg = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID SINGLE_TASK::Remove_Task()
{
	Singleflg = TRUE;
	return;
}

BOOL WaitingTime::WaitTime_OneThrough(int second)
{
	if (Throughflg == FALSE)
	{
	}
	if (Throughflg == TRUE)
	{
		WaitTimer(second*1000);
		return TRUE;
	}
	Throughflg = TRUE;
	return FALSE;
}

VOID WaitingTime::WaitTime_New()
{
	Throughflg = FALSE;
}

