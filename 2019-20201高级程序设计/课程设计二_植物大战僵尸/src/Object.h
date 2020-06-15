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
	
	int damage;		//������
	int speed;		//�ٶ�
	int attackspeed;//�����ٶ�
	int price;		//������Ҫ������
public:
	int life;		//����ֵ
	point pos;		//����
	int tag;		//���ֲ���ʬ�����
	Base(point p,int t=0);
	virtual ~Base();
	virtual void Action() = 0;   //ÿ��ֲ���ʬ���ص�/����

};

class SunFlower :public Base
{
private:
	unsigned long long recordTick;	//ʱ��ʱ��
public:
	SunFlower(point pos, int t = 0);
	~SunFlower();
	void Action();
};

class PeaShooter :public Base
{
private:
	unsigned long long recordTick;	//ʱ��ʱ��
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
	unsigned long long recordTick;	//ʱ��ʱ��
	
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
	unsigned long long recordTick;	//ʱ��ʱ��
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
	unsigned long long recordTick;	//ʱ��ʱ��
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
