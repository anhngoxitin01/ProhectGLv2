#include "Boss.h"

Boss::Boss() : boss_time_use_skill(0) ,skill_boss_is_using_skill(-1.0f) , boss_hp(10) , boss_time_coll_with_waterboom(0)
{
}

Boss::Boss(Enermy e) : boss_time_use_skill(0), skill_boss_is_using_skill(-1.0f) , boss_hp(10) , boss_time_coll_with_waterboom(0)
{
	e.setSpeed(1);
	boss_enermy = e;
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

float Boss::skillIsUsingSkill()
{
	return skill_boss_is_using_skill;
}

void Boss::setSkillIsUsingSkill(float skill)
{
	skill_boss_is_using_skill = skill;
}

int Boss::getHpBoss()
{
	return boss_hp;
}

void Boss::setHpBoss(int newHp)
{
	boss_hp = newHp;
}

void Boss::decreaseHpBoss()
{
	boss_hp -= 1;
}

float Boss::getTimeCollWithWB()
{
	return boss_time_coll_with_waterboom;
}

void Boss::addTimeCollWithWB(float addTime)
{
	boss_time_coll_with_waterboom += addTime;
}

void Boss::setTimeCollWithWB(float newTime)
{
	boss_time_coll_with_waterboom = newTime;
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
	switch (boss_enermy.getDirection())
	{
	case ENERMY_MOVE_DOWN:
	{
		//cacul the number block from enermy to the map border
		int range = MAP_SIZE_Y  - (int)(boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = boss_enermy.getRect().getRecX() - (1 - column) * Globals::item_size;
				float y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + i * Globals::item_size + Globals::item_size / 2;
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
		int range = (int)(boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth()/2 - i * Globals::item_size - Globals::item_size / 2;
				float y = boss_enermy.getRect().getRecY() + (column - 1) * Globals::item_size ;
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
		int range = (int)(boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2) / Globals::item_size - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = boss_enermy.getRect().getRecX() - (column - 1) * Globals::item_size;
				float y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - i * Globals::item_size - Globals::item_size / 2;
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
		int range = MAP_SIZE_Y - (int)(boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2) / Globals::item_size  - 1;
		for (int i = 0; column < 3; i++)
		{
			if (i == range)
			{
				column++;
				i = -1;
				continue;
			}
			else {
				float x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + i * Globals::item_size + Globals::item_size / 2;
				float y = boss_enermy.getRect().getRecY() + (column - 1) * Globals::item_size;
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

void Boss::useSkill_2(int phase)
{
	//clear the data of water boom
	boss_list_waterBoom.clear();

	switch (phase)
	{
	case 1: // 16 recTangle
		// 0 -> 3 up
		// 4 -> 7 right
		// 8 -> 11 down
		// 12 -> 15 left

		for (int i = 0; i < 16; i++)
		{
			float x, y;
			if(i<=3) // up
			{
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size / 2;
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size / 2 + i * Globals::item_size;
			}
			else if(i<=7) // right
			{
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size / 2 + (i - 4) * Globals::item_size;
				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size / 2;
			}
			else if(i<=11) //down
			{
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size / 2;
				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size / 2 - (i - 8) * Globals::item_size;
			}
			else if(i<=15) // left
			{
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size / 2 - (i - 12) * Globals::item_size;
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size / 2;
			}
			//create rec and add to list
			MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
			WaterBoom* wb = new WaterBoom(recWB, "bombbang_mid.tga");
			boss_list_waterBoom.push_back(wb);
		}
		break;
	case 2://24 Rectangle
		//0-> 5 up
		//6 -> 11 right
		//12 ->17 down
		//18 -> 23	left
		for (int i = 0; i < 24; i++)
		{
			float x;
			float y;
			if(i<=5) // up
			{
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size * 3 / 2 + i * Globals::item_size;
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size * 3 / 2;
			}
			else if(i<=11)	// right
			{
				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size * 3 / 2;
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size * 3 / 2 + (i - 6) * Globals::item_size;
			}
			else if(i<=17) //down
			{

				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size * 3 / 2 - (i-12) * Globals::item_size;
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size * 3 / 2;
			}
			else if(i<=23) // left
			{
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size * 3 / 2;
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size * 3 / 2 - (i-18) * Globals::item_size;
			}
			//create rec and add to list
			MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
			WaterBoom* wb = new WaterBoom(recWB, "bombbang_mid.tga");
			boss_list_waterBoom.push_back(wb);
		}
		break;
	case 3://32 Rectangle
		//0-> 7 up
		//8 -> 15 right
		//16 ->23 down
		//23 -> 31	left
		float x;
		float y;
		for (int i = 0; i < 32; i++)
		{
			if (i <= 7) // up
			{
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size * 5 / 2 + i * Globals::item_size;
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size * 5 / 2;
			}
			else if (i <= 15)	// right
			{
				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size * 5 / 2;
				y = boss_enermy.getRect().getRecY() - boss_enermy.getRect().getRecHeight() / 2 - Globals::item_size * 5 / 2 + (i - 8) * Globals::item_size;
			}
			else if (i <= 23) //down
			{

				x = boss_enermy.getRect().getRecX() + boss_enermy.getRect().getRecWidth() / 2 + Globals::item_size * 5 / 2 - (i - 16) * Globals::item_size;
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size * 5 / 2;
			}
			else if (i <= 31) // left
			{
				x = boss_enermy.getRect().getRecX() - boss_enermy.getRect().getRecWidth() / 2 - Globals::item_size * 5 / 2;
				y = boss_enermy.getRect().getRecY() + boss_enermy.getRect().getRecHeight() / 2 + Globals::item_size * 5 / 2 - (i - 24) * Globals::item_size;
			}
			//create rec and add to list
			MRectangle recWB = MRectangle(x, y, Globals::item_size, Globals::item_size);
			WaterBoom* wb = new WaterBoom(recWB, "bombbang_mid.tga");
			boss_list_waterBoom.push_back(wb);
		}
		break;
	default:
		printf("Out of phase range\n");
		break;
	}
}

void Boss::clearWaterBoom()
{
	boss_list_waterBoom.clear();
}

Enermy* Boss::getEnermy()
{
	return &boss_enermy;
}
