#pragma once
struct point
{
	int x;
	int y;
	point(int i = 0, int j = 0) { x = i; y = j; }
};


class Base
{
protected:
	
	int damage;		//攻击力
	int speed;		//速度
	int attackspeed;//攻击速度
	int price;		//购买需要阳光数
public:
	int life;		//生命值
	point pos;		//坐标
	int tag;		//标记植物或僵尸的类别
	Base(point p,int t=0);
	virtual ~Base();
	virtual void Action() = 0;   //每个植物或僵尸的特点/动作

};

class SunFlower :public Base
{
private:
	unsigned long long recordTick;	//时间时钟
public:
	SunFlower(point pos, int t = 0);
	~SunFlower();
	void Action();
};

class PeaShooter :public Base
{
private:
	unsigned long long recordTick;	//时间时钟
public:
	PeaShooter(point pos, int t = 0);
	~PeaShooter();
	void Action();
};

class Nuts :public Base
{
private:
public:
	Nuts(point pos, int t = 0);
	~Nuts();
	void Action();
};

class HotPepper :public Base
{
private:
public:
	HotPepper(point pos, int t = 0);
	~HotPepper();
	void Action();
};

class NormalZombie :public Base
{
private:
	unsigned long long recordTick;	//时间时钟
	
public:
	NormalZombie(point pos, int t = 0);
	~NormalZombie();
	void Walk();
	void Attack();
	void Action();
};

class ConeheadZombie :public Base
{
private:
	unsigned long long recordTick;	//时间时钟
public:
	ConeheadZombie(point pos, int t = 0);
	~ConeheadZombie();
	void Walk();
	void Attack();
	void Action();
};

class BucketZombie :public Base
{
private:
	unsigned long long recordTick;	//时间时钟
public:
	BucketZombie(point pos, int t = 0);
	~BucketZombie();
	void Walk();
	void Attack();
	void Action();
};

class Bullet
{
private:
	point pos;
	int damage;
public:
	friend class Base;
	friend class Game;
	Bullet(point p);
	~Bullet();
	void Action();
};
