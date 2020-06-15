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
	static int coordinate[8][5]; //��ͼ����,
	static Base* BaseTable[8][5];   //��¼ÿһ���Ľ�ʬ��ֲ��
	static list<Bullet*> BulletTable;
	static int sunshine;
	static int score;
	point shop_pos;//�����Ƥʱ��������
	bool Isbuy;//�Ƿ��ڹ���ֲ���״̬
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
	void Init();  //��ʼ������ӡ����Ҫˢ�µĽ���
	void UpdateDraw(); //ˢ�½���
	void KeyBoardControl(); //��ؼ�������
	void Processing();  //��Ϸ���̵Ĵ���
	void BulletUpdate(); //�ӵ��ĸ���
	void ZombiesUpdate(); //��ʬ�ĸ���
};
