#pragma once
#include<vector>
#include<list>
#include"API.h"
#include<string>
#include<iostream>
#include"Object.h"

using namespace std;

class Game
{
private:
	static int coordinate[8][5]; //地图坐标,
	static Base* BaseTable[8][5];   //记录每一个的僵尸或植物
	static list<Bullet*> BulletTable;
	static int sunshine;
	static int score;
	point shop_pos;//购买地皮时所用坐标
	bool Isbuy;//是否处于购买植物的状态
	int tag;
	unsigned long long recordtick;
public:
	static bool state;
	Game();
	~Game() {}
	friend class Base;
	friend class SunFlower;
	friend class PeaShooter;
	friend class HotPepper;
	friend class NormalZombie;
	friend class ConeheadZombie;
	friend class BucketZombie;
	friend class Nuts;
	friend class Bullet;
	void Init();  //初始化，打印不需要刷新的界面
	void UpdateDraw(); //刷新界面
	void KeyBoardControl(); //监控键盘输入
	void Processing();  //游戏进程的处理
	void BulletUpdate(); //子弹的更新
	void ZombiesUpdate(); //僵尸的更新
};
