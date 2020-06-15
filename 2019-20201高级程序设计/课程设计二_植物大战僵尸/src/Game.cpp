#include"Game.h"
#include"API.h"
#include <cassert>
#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;

int Game::sunshine = 50;
int Game::score = 0;
int Game::coordinate[8][5] = { 0 };
bool Game::state = true;
Base* Game::BaseTable[8][5] = { NULL };
list<Bullet*> Game::BulletTable;

Game::Game()
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 5; j++)
			coordinate[i][j] = 0;
	shop_pos = { 0,0 };
	Isbuy = false;
	tag = 0;
	recordtick = GetTickCount64();
}

void Game::Init()
{
	ChangeTitle("Plants.VS.Zombies");
	system("color E5");
	gotoXY(29, 1);
	cout << "JYH's Plants VS Zombies";
	gotoXY(2, 1);
	cout << "score:";
	for (int j = 23; j <= 25; j += 2)
	{
		gotoXY(0, j);
		for (int i = 0; i < 80; i++)
			cout << '=';
	}
	gotoXY(0, 29);
	for (int i = 0; i < 80; i++)
		cout << '=';

	//��ӡ�̵�
	gotoXY(4, 24);
	cout << "�̵�";
	//��ӡ�̵�
	gotoXY(1, 26);
	cout << "1.���տ�:50";
	gotoXY(16, 26);
	cout << "2.�㶹����:100";
	gotoXY(1, 27);
	cout << "3.���:50";
	gotoXY(16, 27);
	cout << "4.������:125";
	gotoXY(50, 24);
	cout << "����:";//sunshine����(55,24);
	gotoXY(84, 13);
	cout << "1.��ͨ��ʬ";
	gotoXY(84, 14);
	cout << "2.·�Ͻ�ʬ";
	gotoXY(84, 15);
	cout << "3.��Ͱ��ʬ";
}

void Game::UpdateDraw()
{

	//��ӡ������Ϸ�仯��ͼ��ֲ��ͽ�ʬ��
	gotoXY(0, 2);
	for (int i = 0; i < 5; i++)
	{
		setColor(237);
		for (int j = 0; j < 80; j++) cout << '#';
		cout << endl;
		for (int h = 0; h < 8; h++)
		{
			//��ӡ�̵�ѡ��Ƥ��־
			if (Isbuy && shop_pos.x == h && shop_pos.y == i)
				cout << "#��       ";
			else cout << "#         ";
		}
		cout << endl;

		for (int h = 0; h < 8; h++)
		{
			switch (coordinate[h][i])
			{
			case 1:setColor(226); cout<< "#���տ�   "; break;
			case 2:setColor(226); cout << "#�㶹���� "; break;
			case 3:setColor(226); cout << "#���     "; break;
			case 4:setColor(226); cout << "#������ "; break;
			case -1:setColor(224); cout << "#��ͨ��ʬ "; break;
			case -2:setColor(224); cout << "#·�Ͻ�ʬ "; break;
			case -3:setColor(224); cout << "#��Ͱ��ʬ "; break;
			default:
				setColor(237); cout << "#         "; break;
			}
			
		}
		cout << endl;
		setColor(237);
		for (int h = 0; h < 8; h++)
		{
			if (coordinate[h][i] == 0)
			{
				cout << setiosflags(ios::left)<< setw(10) << '#';
			}
			else
			{
				cout<<"#  ";
				cout << setiosflags(ios::left)<< setw(7) << BaseTable[h][i]->life;
			}
		}
		cout << endl;
	}
	setColor(237);
	for (int j = 0; j < 80; j++) cout << '#';

	//��ӡ�������ͷ���
	gotoXY(55, 24);
	cout << sunshine;
	gotoXY(8, 1);
	cout << score;

	//��ӡ�ӵ�
	setColor(228);
	for (auto it = BulletTable.begin(); it != BulletTable.end(); it++)
	{
		
		point tmp = (*it)->pos;
		gotoXY(tmp.x, pos_y(tmp.y));
		cout << "��";
	}


}

void Game::KeyBoardControl()
{
	if (IsKeyDown('1'))
	{
		Isbuy = true;
		tag = 1;
	}
	if (IsKeyDown('2'))
	{
		Isbuy = true;
		tag = 2;
	}
	if (IsKeyDown('3'))
	{
		Isbuy = true;
		tag = 3;
		
	}
	if (IsKeyDown('4'))
	{
		Isbuy = true;
		tag = 4;
	}
	if (IsKeyDown('W') && Isbuy)
	{
		if(shop_pos.y >0)
			shop_pos.y -= 1;
	}
	if (IsKeyDown('S')&&Isbuy)
	{
		if(shop_pos.y<4)
			shop_pos.y+=1;
	}
	if (IsKeyDown('A') &&Isbuy)
	{
		if (shop_pos.x > 0)
			shop_pos.x -= 1;
	}
	if (IsKeyDown('D') && Isbuy)
	{
		if (shop_pos.x < 6)
			shop_pos.x += 1;
	}
	if (IsKeyDown(VK_RETURN)&&Isbuy)
	{
		Isbuy = false;
		if (coordinate[shop_pos.x][shop_pos.y] != 0) return;
		coordinate[shop_pos.x][shop_pos.y] = tag;
		switch (tag)
		{
		case 1: if (sunshine < 50) return; BaseTable[shop_pos.x][shop_pos.y] = new SunFlower(shop_pos, 1); sunshine -= 50;  break;
		case 2:	if (sunshine < 100) return; BaseTable[shop_pos.x][shop_pos.y] = new PeaShooter(shop_pos, 2); sunshine -= 100;break;
		case 3:	if (sunshine < 50) return;  BaseTable[shop_pos.x][shop_pos.y] = new Nuts(shop_pos, 3); sunshine -= 50;  break;
		case 4:	if (sunshine < 125) return;  BaseTable[shop_pos.x][shop_pos.y] = new HotPepper(shop_pos, 1); sunshine -= 50; break;
		default:
			break;
		}
	}
	if (IsKeyDown(VK_SPACE))
	{
		gotoXY(80, 25);
		system("pause");
	}
}

void Game::Processing()
{
	for(int i=0;i<8;i++)
		for (int j = 0; j < 5; j++)
		{
			if (BaseTable[i][j] != NULL)
			{
				if (i!=7&&BaseTable[i][j]->tag < 0)	//�����ӵ��Ƿ�򵽽�ʬ
				{
					auto it = BulletTable.begin();
					for (; it != BulletTable.end();)
					{
						//(*it)->Action();
						if ((*it)->pos.x >=pos_x(BaseTable[i][j]->pos.x)&&(*it)->pos.y==BaseTable[i][j]->pos.y)
						{
							BaseTable[i][j]->life -= (*it)->damage;
							(*it)->~Bullet();
							it = BulletTable.erase(it);
						}
						else it++;
					}
				}
				BaseTable[i][j]->Action();	//�������󣬴���ֲ��ͽ�ʬ�Ķ���
			}
		}
	unsigned long long curtick = GetTickCount64();
	if (curtick - recordtick >= 1500&&curtick-recordtick<=2000)
	{
		sunshine += 25;
		//recordtick=curtick;
	}
}

void Game::BulletUpdate()
{
	auto it = BulletTable.begin();
	for (; it != BulletTable.end();)
	{
		(*it)->Action();
		if (((*it)->pos).x >= 70)
		{
			(*it)->~Bullet();
			it = BulletTable.erase(it);
		}
		else it++;
	}
}

void Game::ZombiesUpdate()
{
	unsigned long long curtick = GetTickCount64();
	if (curtick - recordtick >= 6000)
	{
		int y = rand() % 5;
		int t = rand() % 5;
		int tag = 0;
		if (t == 0) tag = 2;
		else if (t == 1) tag = 3;
		else tag = 1;
		if(coordinate[7][y] != 0)
		{
			return;
		}
		switch (tag)
		{
		case 1:BaseTable[7][y] = new NormalZombie({ 7,y }, -1);break;
		case 2:BaseTable[7][y] = new ConeheadZombie({ 7,y }, -2); break;
		case 3:BaseTable[7][y] = new BucketZombie({ 7,y }, -3); break;
		default:
			break;
		}
		recordtick = curtick;
	}
}