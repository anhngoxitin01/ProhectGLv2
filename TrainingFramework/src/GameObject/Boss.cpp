#include "Boss.h"

Boss::Boss()
{
}

Boss::Boss(Enermy e)
{
	e.setSpeed(1);
	enermy = e;
}

Boss::~Boss()
{
}

void Boss::clearWaterBoom()
{
	boss_list_waterBoom.clear();
}

Enermy* Boss::getEnermy()
{
	return &enermy;
}
