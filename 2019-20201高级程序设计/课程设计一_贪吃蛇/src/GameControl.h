#pragma once
#include<Windows.h>
#include"GreedySnake.h"
class Game
{
private:
	bool GameState;
	Map map;
	Food food;
	Snake snake;
	int cur_move;

public:
	Game() { GameState = true; cur_move = 0; }
	bool IsKeyDown(int key);
	void KeyboardControl();
	bool EatOrdinaryFood(list<Point>& body, Point pos);	//����Ե�ʳ���β�͸���һ��ӵ�β����

	bool EatLimitedFood(list<Point>& body, Point& pos2);
	void Running();
};