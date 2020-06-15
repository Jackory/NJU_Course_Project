#include"API.h"
void gotoXY(int x, int y) //��λ���
{
	COORD pos{ x, y };
	HANDLE Hout = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���
	SetConsoleCursorPosition(Hout, pos);
}

void HideCursor() //���ع��
{
	CONSOLE_CURSOR_INFO curInfo;
	HANDLE Hout = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���
	curInfo.dwSize = 1;				// ���û��ֵ�Ļ������ع����Ч
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