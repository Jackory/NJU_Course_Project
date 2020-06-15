#include<Windows.h>
#include"GameControl.h"
bool Game::IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}
void Game::KeyboardControl()
{
	if (IsKeyDown(VK_ESCAPE)) // esc键按下则退出循环结束游戏
	{
		GameState = false;
		return;
	}
	if (IsKeyDown(VK_LEFT))
	{
		snake.ChangeDir(Direction::left);
	}
	if (IsKeyDown(VK_RIGHT))
	{
		snake.ChangeDir(Direction::right);
	}

	if (IsKeyDown(VK_UP))
	{
		snake.ChangeDir(Direction::up);
	}

	if (IsKeyDown(VK_DOWN))
	{
		snake.ChangeDir(Direction::down);
	}
}
bool Game::EatOrdinaryFood(list<Point>& body, Point pos)	//如果吃到食物，将尾巴复制一遍加到尾巴上
{
	if (body.front().x == Food::pos.x && body.front().y == Food::pos.y)
	{
		Point tmp = body.back();
		body.push_back(tmp);
		snake.lenth++;
		snake.score += 5;
		food.FoodUpdate();
		return true;
	}
	return false;

}
bool Game::EatLimitedFood(list<Point>& body, Point& pos2)
{
	if (body.front().x == Food::pos2.x && body.front().y == Food::pos2.y)
	{
		Point tmp = body.back();
		body.push_back(tmp);
		snake.lenth++;
		snake.score += 10;
		pos2.x = 0; pos2.y = 0;
		return true;
	}
	return false;
}
void Game::Running()
{
	while (!snake.IsDie() && GameState)
	{
		KeyboardControl();
		snake.Move();
		snake.Dead();
		EatOrdinaryFood(snake.body, food.pos);
		if (food.val == 5)
		{
			EatLimitedFood(snake.body, food.pos2);
			if (cur_move == 0)
				cur_move = snake.num_move;
			if (snake.num_move - cur_move == 30 && !(food.pos2.x != 0 && food.pos2.y != 0))
			{
				gotoXY(food.pos2.x, food.pos2.y);
				cout << "□";
			}
		}
		Sleep(200);
	}
	gotoXY(N / 2, N / 2);
	cout << " 游戏结束  ";
	gotoXY(0, N + 5);
}