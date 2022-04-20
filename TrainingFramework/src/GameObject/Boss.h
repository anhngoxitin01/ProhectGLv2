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

	

	//skill
	float	getTimeUseSkill();
	void	setTimeUseSkill(float time);
	void	addTimeUseSkill(float time);
	float	skillIsUsingSkill();
	void	setSkillIsUsingSkill(float skill);
	bool	checkTimeUseSkill();
	void	useSkill_1();
	void    useSkill_2(int phase);

	//hp
	int		getHpBoss();
	void	setHpBoss(int newHp);
	void	decreaseHpBoss();
	//time coll boom
	float	getTimeCollWithWB();
	void	addTimeCollWithWB(float addTime);
	void	setTimeCollWithWB(float newTime);

	int		findDirectionPlayer(MRectangle pl);

	
	std::list<WaterBoom*>* getListWaterBoom();
	void	clearWaterBoom();
	Enermy*	getEnermy();
private:
	Enermy					boss_enermy;
	int						boss_skills[1];
	std::list<WaterBoom*>	boss_list_waterBoom;
	float					boss_time_use_skill;
	float					skill_boss_is_using_skill;
	float					boss_time_coll_with_waterboom;
	int						boss_hp;
};