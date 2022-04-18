#include "Boss.h"

Boss::Boss() : boss_time_use_skill(0)
{
}

Boss::Boss(Enermy e) : boss_time_use_skill(0) 
{
	e.setSpeed(1);
	enermy = e;
}

Boss::~Boss()
{
}

float Boss::getTimeUseSkill()
{
	return boss_time_use_skill;
}

void Boss::setTimeUseSkill(float time)
{
	boss_time_use_skill = time;
}

void Boss::addTimeUseSkill(float time)
{
	boss_time_use_skill += time;
}

std::list<WaterBoom*>* Boss::getListWaterBoom()
{
	return &boss_list_waterBoom;
}

bool Boss::checkTimeUseSkill()
{
	if(boss_time_use_skill >= TIME_USE_SKILL)
		return true;
	return false;
}

void Boss::useSkill_1()
{
	//clear the data of water boom
	boss_list_waterBoom.clear();

	//generate wb
	int column = 0;
	switch (enermy.getDirection())
	{
	case ENERMY_MOVE_DOWN:
	{
		//cacul the number block from enermy to the map border
		int range = MAP_SIZE_Y  - (int)(enermy.getRect().getRecY() + enermy.getRect().getRecHeight() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = enermy.getRect().getRecX() - (1 - column) * Globals::item_size;
				float y = enermy.getRect().getRecY() + enermy.getRect().getRecHeight() / 2 + i * Globals::item_size + Globals::item_size / 2;
				MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
				WaterBoom* wb = new WaterBoom(recWB, "bombbang_down_1.tga");
				boss_list_waterBoom.push_back(wb);
			}
		}
		break;
	}
	case ENERMY_MOVE_LEFT:
	{
		//cacul the number block from enermy to the map border
		int range = (int)(enermy.getRect().getRecX() - enermy.getRect().getRecWidth() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = enermy.getRect().getRecX() - enermy.getRect().getRecWidth()/2 - i * Globals::item_size - Globals::item_size / 2;
				float y = enermy.getRect().getRecY() + (column - 1) * Globals::item_size ;
				MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
				WaterBoom* wb = new WaterBoom(recWB, "bombbang_left_1.tga");
				boss_list_waterBoom.push_back(wb);
			}
		}
		break;
	}	
	case ENERMY_MOVE_UP:
	{
		//cacul the number block from enermy to the map border
		int range = (int)(enermy.getRect().getRecY() - enermy.getRect().getRecHeight() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = enermy.getRect().getRecX() - (column - 1) * Globals::item_size;
				float y = enermy.getRect().getRecY() - enermy.getRect().getRecHeight() / 2 - i * Globals::item_size - Globals::item_size / 2;
				MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
				WaterBoom* wb = new WaterBoom(recWB, "bombbang_up_1.tga");
				boss_list_waterBoom.push_back(wb);
			}
		}
		break;
	}
	case ENERMY_MOVE_RIGHT:
	{
		//cacul the number block from enermy to the map border
		int range = MAP_SIZE_Y - (int)(enermy.getRect().getRecX() + enermy.getRect().getRecWidth() / 2) / Globals::item_size  - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = enermy.getRect().getRecX() + enermy.getRect().getRecWidth() / 2 + i * Globals::item_size + Globals::item_size / 2;
				float y = enermy.getRect().getRecY() + (column - 1) * Globals::item_size;
				MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
				WaterBoom* wb = new WaterBoom(recWB, "bombbang_right_1.tga");
				boss_list_waterBoom.push_back(wb);
			}
		}
		break;
	}
	default:
		break;
	}
}

void Boss::clearWaterBoom()
{
	boss_list_waterBoom.clear();
}

Enermy* Boss::getEnermy()
{
	return &enermy;
}
