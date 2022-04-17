#pragma once
#include "GameConfig.h"
#include "MRectangle.h"
#include "Enermy.h"
#include "WaterBoom.h"
#include <list>

class Boss
{
public:
	Boss();
	Boss(Enermy e);
	~Boss();

	void	clearWaterBoom();
	Enermy*	getEnermy();
private:
	Enermy					enermy;
	int						skills[1];
	std::list<WaterBoom*>	boss_list_waterBoom;
};