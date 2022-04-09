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

void Boom::setListWaterBoom(std::list<WaterBoom> lWB)
{
	for (auto x : lWB)
	{
		b_list_water_boom.push_back(x);
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


void Boom::removeWaterBoom(WaterBoom wb)
{
	auto index = b_list_water_boom.insert(b_list_water_boom.end(), wb);
	b_list_water_boom.erase(index);
	printf("\n\n%d\n\n", b_list_water_boom.size());
}

void Boom::updateWaterBoom()
{
	removeWaterBoom(*b_list_water_boom.begin());
}

