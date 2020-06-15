#include"GreedySnake.h"
Point Food::pos = { 0,0 };
Point Food::pos2 = { 0,0 };
int Snake::num_move = 0;
list<Point> Snake::body;
//"★" "■" "□" "●"
void gotoXY(int x, int y)
{
	COORD pos{ x*2 , y };
	HANDLE Hout = GetStdHandle(STD_OUTPUT_HANDLE); //获取句柄
	SetConsoleCursorPosition(Hout, pos);
}

void setColor(int vis)
{
	HANDLE Hout;
	Hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Hout, vis);
}

//用蛇改变方向时，改变蛇头坐标
int Xoffset[4] = { 0,0,-1,1 };
int Yoffset[4] = { -1,1,0,0 };

void Snake::Reset()
{
	body.clear();
	Point head = { 5, 5 };
	Point pos1 = { 4,5 };
	Point pos2 = { 3,5 };
	body.push_back(head);
	body.push_back(pos1);
	body.push_back(pos2);
	score = 0;
	lenth = 3;
	isalive = true;
	dir = Direction::right;
	Draw();

}
void Snake::ChangeDir(Direction set_dir)
{
	//首先判断蛇的移动是否常识
	if (set_dir == Direction::up && dir == Direction::down
		|| set_dir == Direction::down && dir == Direction::up
		|| set_dir == Direction::left && dir == Direction::right
		|| set_dir == Direction::right && dir == Direction::left)
	{
		return;
	}
	dir = set_dir;
}


void Snake::Move()
{
	if (isalive)
	{
		Point tail = { body.back().x,body.back().y };
		gotoXY(tail.x, tail.y);
		setColor(11);
		cout << "□";
		num_move++;

		list<Point>::iterator it = body.begin();


		int pre_x = (*it).x; //临时存放即将改变的坐，方便后续坐标的改变
		int pre_y = (*it).y;

		it->x += Xoffset[dir]; //改变蛇头坐标
		it->y += Yoffset[dir];
		it++;
		for (; it != body.end(); it++) //将后续蛇结点全部前移
		{
			int tmp_x = it->x;
			int tmp_y = it->y;

			it->x = pre_x;
			it->y = pre_y;

			pre_x = tmp_x;
			pre_y = tmp_y;
		}
		Draw();
	}
}
void Snake::Draw()
{
	list<Point>::iterator it = body.begin();
	setColor(13);
	gotoXY((*it).x, (*it).y);
	cout << "●";
	it++;
	for (; it != body.end(); it++)
	{
		gotoXY((*it).x, (*it).y);
		cout << "■";
	}
	gotoXY(33, 11);
	setColor(15);
    cout << score;
}
void Snake::Dead()
{
	if (isalive == false) return ;
	//蛇头撞墙
	if (body.front().x < 1 || body.front().x>N
		|| body.front().y < 1 || body.front().y>N)
	{
		isalive = false;
	}

	//蛇头撞自己 ，遍历头结点是否与身体重合
	list<Point>::iterator it = body.begin();
	Point headPos = *it;
	++it;
	for (; it != body.end(); ++it)
	{
		// 检查所有节点是否与头节点重合
		if (it->x == headPos.x && it->y == headPos.y)
		{
			isalive = false;
		}
	}
}
void Map::Reset()
{
	//初始化地图与墙
	memset(board, false, sizeof(board));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			board[i][j] = true;
		}
	setColor(11);
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (board[i][j]) cout << "□";
			else cout << "■";
		}
		cout << endl;
	}
	gotoXY(25, 10);
	cout << " 欢迎来到JYH的贪吃蛇世界" << endl;
	gotoXY(27, 11);
	setColor(10);
	cout << "您的分数是";
}
void Food::OrdinaryFood()
{
		//do
		//{
		//	pos.x = rand() % N + 1;
		//	pos.y = rand() % N + 1;
		//	gotoXY(pos.x, pos.y);
		//	setColor(12);
		//	cout << "●" << endl;
		//} while (Overlap(pos, Snake::body));
		//val = (val + 1) % 6;
}
void Food::LimitedFood(int &cur_num_move)
{
		//if (val == 5)
		//{
		//	do
		//	{
		//		pos2.x = rand() % N + 1;
		//		pos2.y = rand() % N + 1;
		//		setColor(12);
		//		gotoXY(pos2.x, pos2.y);
		//		cout << "★" << endl;
		//	} while (Overlap(pos,Snake::body));
		//	int cur_num_move = Snake::num_move;
		//	val = (val + 1) % 6;
		//}
		//else
		//{
		//	pos2.x = 0;
		//	pos2.y = 0;
		//}
}
void Food::FoodUpdate()
{
	do
	{
		pos.x = rand() % N + 1;
		pos.y = rand() % N + 1;
		gotoXY(pos.x, pos.y);
		setColor(12);
		cout << "●" << endl;
	} while (Overlap(pos, Snake::body));
	val = (val + 1) % 6;
	if (val == 5)
	{
		do
		{
			pos2.x = rand() % N + 1;
			pos2.y = rand() % N + 1;
			setColor(12);
			gotoXY(pos2.x, pos2.y);
			cout << "★" << endl;
		} while (Overlap(pos, Snake::body));
	}
}
bool Food::Overlap(Point p,list<Point>& q)
{
	list<Point>::iterator it = q.begin();
	for (; it != q.end(); it++)
	{
		if (it->x == p.x && it->y == p.y)
			return true;
	}
	return false;
}

