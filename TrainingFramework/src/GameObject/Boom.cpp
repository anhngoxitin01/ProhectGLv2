#include "Boom.h"

Boom::Boom() : b_index_boom_exploding(0)  , b_status_boom(STATUS_BOOM_PREPARE_EXPLODE) ,b_time_boom_exploding(0.0f)
{
	b_pathTextureBoom = "boom_animation.tga";
	//increase boom_id in globals
	b_id = Globals::boom_Id++;
	//reset global boom id if it has more than 100
	if (Globals::boom_Id == 100)
		Globals::boom_Id = 0;
}

Boom::~Boom()
{
}

std::string Boom::getPathTextureBoom()
{
	return b_pathTextureBoom;
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

int Boom::getIdBoom()
{
	return b_id;
}

std::list<WaterBoom*>* Boom::getListWaterBoom()
{
	return &b_list_water_boom;
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
	newBoomRec.setRecHeight(Globals::item_size);

	//get the index xy in map where player is standing
	int indexX = playerRec.getRecX() / Globals::item_size;
	int indexY = playerRec.getRecY() / Globals::item_size;

	//get the location xy in map where player is standing
	newBoomRec.setRecXY(
		indexX * Globals::item_size + Globals::item_size / 2
		, indexY * Globals::item_size + Globals::item_size / 2);

	return newBoomRec;
}



