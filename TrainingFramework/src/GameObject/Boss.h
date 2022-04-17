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

	float	getTimeUseSkill();
	void	setTimeUseSkill(float time);
	void	addTimeUseSkill(float time);
	std::list<WaterBoom*>* getListWaterBoom();

	bool	checkTimeUseSkill();

	void	useSkill_1();

	void	clearWaterBoom();
	Enermy*	getEnermy();
private:
	Enermy					enermy;
	int						skills[1];
	std::list<WaterBoom*>	boss_list_waterBoom;
	float					boss_time_use_skill;
};