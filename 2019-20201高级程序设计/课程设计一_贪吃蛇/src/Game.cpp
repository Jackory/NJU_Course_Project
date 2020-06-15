#include"GreedySnake.h"
#include"GameControl.h"
#include<conio.h>
#include<ctime>
int main()
{
	srand(unsigned int(time(NULL)));//设置随机数种子
	Game game;
	game.Running();
	return 0;
}