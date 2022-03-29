#include "Boom.h"

Boom::Boom() : b_index_boom_exploding(0)  , b_status_boom(STATUS_BOOM_PREPARE_EXPLODE) ,b_time_boom_exploding(0.0f)
{
	b_pathTextureBoom[0] = "boom1.tga";
	b_pathTextureBoom[2] = "boom2.tga";
	b_pathTextureBoom[3] = "boom3.tga";
	b_pathTextureBoom[4] = "boom4.tga";
	b_pathTextureBoom[5] = "boom5.tga";
	b_pathTextureBoom[6] = "boom6.tga";
	b_pathTextureBoom[7] = "boom7.tga";
}

Boom::~Boom()
{
}

std::string Boom::getPathTextureBoom(int index)
{
	return b_pathTextureBoom[index];
}

MRectangle Boom::getRect()
{
	return b_rec;
}

int Boom::getPower()
{
	return b_power;
}

int Boom::getIndexBoomExploding()
{
	return b_index_boom_exploding;
}

float Boom::getTimeExploding()
{
	return b_time_boom_exploding;
}

int Boom::getStatusBoom()
{
	return b_status_boom;
}

std::list<WaterBoom> Boom::getListWaterBoom()
{
	return b_list_water_boom;
}

void Boom::setPower(int power)
{
	b_power = power;
}

void Boom::setRec(MRectangle rec)
{
	b_rec = rec;
}

void Boom::setTimeBoomExploding(float timeExploding)
{
	b_time_boom_exploding = timeExploding;
}

void Boom::setIndexBoomExploding(int indexExploding)
{
	b_index_boom_exploding = indexExploding;
}

void Boom::setStatusBoom(int statusBoom)
{
	b_status_boom = statusBoom;
}

void Boom::increaseTimeBoom(float deltaTime)
{
	//icrease time of each boom
	b_time_boom_exploding += deltaTime;

	//TODO
	//update hinh anh hoac chay animation

	//set status for boom
	if (b_time_boom_exploding >= TIME_BOOM_DESTROY)
	{
		b_status_boom = STATUS_BOOM_DESTROY;
	}
	else if (canBoomExplode() && b_status_boom == STATUS_BOOM_PREPARE_EXPLODE)
	{
		b_status_boom = STATUS_BOOM_EXPLODE;
	}
}

bool Boom::canBoomExplode()
{
	return (b_time_boom_exploding >= TIME_BOOM_EXPLORE) ;
}

MRectangle Boom::calculateLocationGenerate(MRectangle playerRec)
{
	//create new Rec for boom
	MRectangle newBoomRec;
	//add value width , lenght
	newBoomRec.setRecWidth(Globals::item_size);
	newBoomRec.setRecLength(Globals::item_size);

	//get the index xy in map where player is standing
	int indexX = playerRec.getRecX() / Globals::item_size;
	int indexY = playerRec.getRecY() / Globals::item_size;

	//get the location xy in map where player is standing
	newBoomRec.setRecXY(
		indexX * Globals::item_size + Globals::item_size / 2
		, indexY * Globals::item_size + Globals::item_size / 2);

	return newBoomRec;
}

void Boom::autoGenerateLocationWaterBoom()
{
	//create tempRec
	MRectangle tempRec;

	for (int i=0 ; i < (b_power * 4 + 1); i++)
	{
		// center water boom
		if (i == 0)
		{
			b_list_water_boom.push_back(WaterBoom(b_rec, "bombbang_mid.tga"));
		}
			
		//	up water boom
		else if (i < b_power)
		{
			tempRec = MRectangle(b_rec.getRecX(), b_rec.getRecY() + Globals::item_size * i, Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_up_1.tga"));
		}
		else if (i == b_power)
		{
			tempRec = MRectangle(b_rec.getRecX(), b_rec.getRecY() + Globals::item_size * i, Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_up_2.tga"));
		}
		//	left water boom
		else if (i < b_power * 2)
		{
			tempRec = MRectangle(b_rec.getRecX() - Globals::item_size * (i - b_power), b_rec.getRecY(), Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_left_1.tga"));
		}
		else if (i == b_power * 2)
		{
			tempRec = MRectangle(b_rec.getRecX() - Globals::item_size * (i - b_power), b_rec.getRecY(), Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_left_2.tga"));
		}
		//	down water boom
		else if (i < b_power * 3)
		{
			tempRec = MRectangle(b_rec.getRecX(), b_rec.getRecY() - Globals::item_size * (i - b_power * 2), Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_down_1.tga"));
		}
		else if (i == b_power * 3)
		{
			tempRec = MRectangle(b_rec.getRecX(), b_rec.getRecY() - Globals::item_size * (i - b_power * 2), Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_down_2.tga"));
		}
		//	right water boom
		else if (i < b_power * 4)
		{
			tempRec = MRectangle(b_rec.getRecX() + Globals::item_size * (i - b_power * 3), b_rec.getRecY() , Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_right_1.tga"));
		}
		else if (i == b_power * 4)
		{
			tempRec = MRectangle(b_rec.getRecX() + Globals::item_size * (i - b_power * 3), b_rec.getRecY(), Globals::item_size, Globals::item_size);
			b_list_water_boom.push_back(WaterBoom(tempRec, "bombbang_right_2.tga"));
		}
		else 
		{
			printf("===Error in auto generrate Boom \n");
		}
	}
}
