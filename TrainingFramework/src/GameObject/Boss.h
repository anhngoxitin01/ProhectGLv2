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
	float	skillIsUsingSkill();
	void	setSkillIsUsingSkill(float skill);
	int		getHpBoss();
	void	setHpBoss(int newHp);
	void	decreaseHpBoss();

	bool	checkTimeUseSkill();

	void	useSkill_1();
	void    useSkill_2(int phase);

	void	clearWaterBoom();
	Enermy*	getEnermy();
private:
	Enermy					boss_enermy;
	int						boss_skills[1];
	std::list<WaterBoom*>	boss_list_waterBoom;
	float					boss_time_use_skill;
	float					skill_boss_is_using_skill;
	int						boss_hp;
};