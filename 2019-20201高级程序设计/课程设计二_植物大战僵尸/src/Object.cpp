#include"Object.h"
#include"Game.h"

Base::Base(point p, int t)
{
	pos = p;
	tag = t;
	attackspeed = 0;
	damage = 0;
	life = 0;
	price = 0;
	speed = 0;
	Game::coordinate[pos.x][pos.y] = tag;
}

Base::~Base()
{
	Game::coordinate[pos.x][pos.y] = 0;
	Game::BaseTable[pos.x][pos.y] = NULL;
}

SunFlower::SunFlower(point p, int t):Base(p,t)
{
	life = 100;
	tag = 1;
	price = 50;
	recordTick = 0;
}

SunFlower::~SunFlower()
{

}

void SunFlower::Action()
{
	if (life == 0) Game::BaseTable[pos.x][pos.y]->~Base();
	unsigned long long curTick = GetTickCount64();
	if (curTick - recordTick >= 1400)
	{
		Game::sunshine += 25;
		recordTick = curTick;
	}
}

PeaShooter::PeaShooter(point p, int t) :Base(p, t)
{
	life = 100;
	attackspeed = 0;
	price = 100;
	recordTick = 0;
}

PeaShooter::~PeaShooter()
{

}

void PeaShooter::Action()
{
	if (life == 0) Game::BaseTable[pos.x][pos.y]->~Base();
	unsigned long long curTick = GetTickCount64();
	if (curTick - recordTick >= 1400)
	{
		Bullet* newbullet = new Bullet(pos);
		Game::BulletTable.push_back(newbullet);
		recordTick = curTick;
	}

}

Nuts::Nuts(point p, int t /*= 0*/) :Base(p, t)
{
	life = 500;
	price = 50;
}

Nuts::~Nuts()
{

}

void Nuts::Action()
{
	if(life<=0) Game::BaseTable[pos.x][pos.y]->~Base();
}

HotPepper::HotPepper(point p, int t /*= 0*/) :Base(p, t)
{
	life = 0;
	price = 125;
}

HotPepper::~HotPepper()
{

}

void HotPepper::Action()
{
	for (int i = 0; i < 7; i++)
	{
		if (Game::coordinate[i][pos.y] < 0)
			Game::BaseTable[i][pos.y]->life = 0;
	}
	if (life <= 0) Game::BaseTable[pos.x][pos.y]->~Base();
}


NormalZombie::NormalZombie(point p, int t) :Base(p, t)
{
	life = 100;
	damage = 25;
	speed = 4;
	attackspeed = 5;
	recordTick = 0;
}

NormalZombie::~NormalZombie()
{
	Game::score += 50;
}

void NormalZombie::Walk()
{
	if (pos.x <=0) Game::state = false;
	else if (Game::coordinate[pos.x - 1][pos.y] == 0) //如果僵尸前一格是空的
	{
		Game::coordinate[pos.x][pos.y] = 0;
		Game::coordinate[pos.x - 1][pos.y] = tag;
		Game::BaseTable[pos.x - 1][pos.y] = Game::BaseTable[pos.x][pos.y];
		Game::BaseTable[pos.x][pos.y] = NULL;
		pos.x--;
	}

}

void NormalZombie::Attack()
{
	//if (pos.x <= 0) Game::state = false;
	if (Game::coordinate[pos.x - 1][pos.y] > 0)  //如果僵尸前一格有植物
	{
		Game::BaseTable[pos.x - 1][pos.y]->life -= damage;
	}
}

void NormalZombie::Action()
{
	if (life <= 0) Game::BaseTable[pos.x][pos.y]->~Base();
	unsigned long long curTick = GetTickCount64();
	if (curTick - recordTick >= 3000)
	{
		Walk();
		Attack();
		recordTick = curTick;
	}


}

ConeheadZombie::ConeheadZombie(point p, int t) :Base(p, t)
{
	life = 300;
	damage = 25;
	speed = 4;
	attackspeed = 5;
	recordTick = 0;
}

ConeheadZombie::~ConeheadZombie()
{
	Game::score += 100;
}

void ConeheadZombie::Walk()
{
	if (pos.x <= 0) Game::state = false;
	else if (Game::coordinate[pos.x - 1][pos.y] == 0) //如果僵尸前一格是空的
	{
		Game::coordinate[pos.x][pos.y] = 0;
		Game::coordinate[pos.x - 1][pos.y] = tag;
		Game::BaseTable[pos.x - 1][pos.y] = Game::BaseTable[pos.x][pos.y];
		Game::BaseTable[pos.x][pos.y] = NULL;
		pos.x--;
	}
}

void ConeheadZombie::Attack()
{
	//if (pos.x <= 0) Game::state = false;
	if (Game::coordinate[pos.x - 1][pos.y] > 0)  //如果僵尸前一格有植物
	{
		Game::BaseTable[pos.x - 1][pos.y]->life -= damage;
	}
}

void ConeheadZombie::Action()
{
	if (life <= 0) Game::BaseTable[pos.x][pos.y]->~Base();
	unsigned long long curTick = GetTickCount64();
	if (curTick - recordTick >= 3000)
	{
		Walk();
		Attack();
		recordTick = curTick;
	}
}

BucketZombie::BucketZombie(point p, int t /*= 0*/) :Base(p, t)
{
	life = 600;
	damage = 25;
	speed = 4;
	attackspeed = 5;
	recordTick = 0;
}

BucketZombie::~BucketZombie()
{
	Game::score += 200;
}

void BucketZombie::Walk()
{
	if (pos.x <= 0) Game::state = false;
	else if (Game::coordinate[pos.x - 1][pos.y] == 0) //如果僵尸前一格是空的
	{
		Game::coordinate[pos.x][pos.y] = 0;
		Game::coordinate[pos.x - 1][pos.y] = tag;
		Game::BaseTable[pos.x - 1][pos.y] = Game::BaseTable[pos.x][pos.y];
		Game::BaseTable[pos.x][pos.y] = NULL;
		pos.x--;
	}

}

void BucketZombie::Attack()
{
	if (Game::coordinate[pos.x - 1][pos.y] > 0)  //如果僵尸前一格有植物
	{
		Game::BaseTable[pos.x - 1][pos.y]->life -= damage;
	}
}

void BucketZombie::Action()
{
	if (life <= 0) Game::BaseTable[pos.x][pos.y]->~Base();
	unsigned long long curTick = GetTickCount64();
	if (curTick - recordTick >= 3000)
	{
		Walk();
		Attack();
		recordTick = curTick;
	}
}


Bullet::Bullet(point p)
{
	pos.x = pos_x(p.x) + 7;
	pos.y = p.y;
	damage = 20;
}

Bullet::~Bullet()
{
	pos.x = 0;
	pos.y = 0;
}

void Bullet::Action()
{
	pos.x += 2;
}