#include"GreedySnake.h"
#include"GameControl.h"
#include<conio.h>
#include<ctime>
int main()
{
	srand(unsigned int(time(NULL)));//�������������
	Game game;
	game.Running();
	return 0;
}