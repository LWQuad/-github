#include "DxLib.h"
#include "mykey_input.hpp"

int KEYINPUT::KEYINPUT_ALLACTION(int INPUT_KEY)
{
	//CheckHitKey
	/* 押されているとき:1 */
	/* 押されていない  :0 */
	if (OldKeyState[INPUT_KEY]== 0)//前回呼び出し時押していない時
	{
		OnlyKeyflg[INPUT_KEY] = TRUE;
	}
	OldKeyState[INPUT_KEY] = CheckHitKey(INPUT_KEY);
	if (CheckHitKey(INPUT_KEY) == TRUE && OnlyKeyflg[INPUT_KEY] == TRUE)
	{
		OnlyKeyflg[INPUT_KEY] = FALSE;
		return 0;	//キーを押している

	}
	if (OldKeyState[INPUT_KEY] >= 1 && OnlyKeyflg[INPUT_KEY] == TRUE)
	{
		return 1;
	}
	else {return -1; }

}

int KEYINPUT::KEYINPUT_NORMAL(int INPUT_KEY)
{
	OldKeyState[INPUT_KEY] == CheckHitKey(INPUT_KEY);
	if (CheckHitKey(INPUT_KEY) == TRUE)
	{
		return 0;
	}
	else { return-1; }
}

int KEYINPUT::KEYINPUT_UP(int INPUT_KEY)
{
	if (OldKeyState[INPUT_KEY] >= 1 && CheckHitKey(INPUT_KEY) == 0)
	{
		return 0;
	}
	else { return -1; }
}