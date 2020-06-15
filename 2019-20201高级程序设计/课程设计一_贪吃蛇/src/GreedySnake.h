#pragma once
#include<Windows.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<list>
using namespace std;
const int N = 21;
enum Direction { up, down, left, right };

struct Point
{
	int x, y;
};


void gotoXY(int x, int y);		//光标跳转到指定位置
void setColor(int colorId);		//设置输出颜色


//创建蛇类
class Snake
{
private:
	static list<Point> body;  //蛇身
	int lenth;        //蛇长
	static int num_move;     //移动次数
	Direction dir;   //方向
	bool isalive;     //是否存活
	int score;
public:
	friend class Game;
	friend class Food;
	Snake() { Reset(); }
	~Snake() {}
	void ChangeDir(Direction set_dir);
	void Move();
	void Draw();
	void Reset();
	void Dead();
	bool IsDie() { return !isalive; }
	int Num_Move() { return num_move; }
};

class Map
{
private:
	bool board[N + 5][N + 5];
public:
	Map() { Reset(); }
	~Map(){}
	void Reset();

};

class Food
{
private:
	static Point pos;
	static Point pos2;
	int val;  //标记食物的出现，五次OrdinaryFood 一次LimitedFood
public:
	friend class Game;
	Food() { Reset();  }
	~Food() {}
	void Reset() { val = 0; FoodUpdate(); }
	void FoodUpdate();
	void OrdinaryFood();
	void LimitedFood(int& cur_num_move);
	bool Overlap(Point p, list<Point>& q);
	
};