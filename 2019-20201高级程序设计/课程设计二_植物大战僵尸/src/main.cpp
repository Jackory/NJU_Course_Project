#include<iostream>
#include"Game.h"
#include<time.h>
using namespace std;

int main()
{
	srand((int)time(0));//设置随机数种子
	Game game;
	game.Init();
	HideCursor();
	while (Game::state != 0)
	{
		game.UpdateDraw();
		game.KeyBoardControl();
		game.Processing();
		game.ZombiesUpdate();
		game.BulletUpdate();
		Sleep(50);
		//gotoXY(80, 25);
		//cout << "■";
	}
	gotoXY(45, 13);
	cout << "You Lose";
	return 0;
}