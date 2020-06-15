#include"API.h"
void gotoXY(int x, int y) //定位光标
{
	COORD pos{ x, y };
	HANDLE Hout = GetStdHandle(STD_OUTPUT_HANDLE); //获取句柄
	SetConsoleCursorPosition(Hout, pos);
}

void HideCursor() //隐藏光标
{
	CONSOLE_CURSOR_INFO curInfo;
	HANDLE Hout = GetStdHandle(STD_OUTPUT_HANDLE); //获取句柄
	curInfo.dwSize = 1;				// 如果没赋值的话，隐藏光标无效
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(Hout, &curInfo);
}

void ChangeTitle(const char* str)
{
	SetConsoleTitle(str);
}

void setColor(int wAttributes)
{
	HANDLE Hout;
	Hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Hout, wAttributes);
}

bool IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}