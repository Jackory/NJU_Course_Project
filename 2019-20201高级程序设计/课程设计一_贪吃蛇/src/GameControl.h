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
	bool EatOrdinaryFood(list<Point>& body, Point pos);	//如果吃到食物，将尾巴复制一遍加到尾巴上

	bool EatLimitedFood(list<Point>& body, Point& pos2);
	void Running();
};